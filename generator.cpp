#include <iostream>
#include <cmath>
#include <ctime>
#include <fstream>
#include <cstdlib>

class Matrix {
public:
    double **a;
    int n;
public:
    explicit Matrix(int size) {
        a = new double *[size];
        n = size;
        for (int i = 0; i < size; i++) {
            a[i] = new double[size];
            for (int j = 0; j < n; j++) {
                a[i][j] = 0;
            }
        }
    }

    void generate() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                a[i][j] = (double) rand() / RAND_MAX * 300 - 150;
            }
        }
        *this = this->transpose() * (*this);
    }


    Matrix(const Matrix &m) {
        n = m.n;
        a = new double *[n];
        for (int i = 0; i < n; i++) {
            a[i] = new double[n];
            for (int j = 0; j < n; j++) {
                a[i][j] = m.a[i][j];
            }
        }
    }

    Matrix &operator=(const Matrix &m) {
        if (this != &m) {
            for (int i = 0; i < n; i++) {
                delete[] a[i];
            }
            for (int i = 0; i < n; i++) {
                a[i] = new double[n];
                for (int j = 0; j < n; j++) {
                    a[i][j] = m.a[i][j];
                }
            }
        }
        return *this;
    }

    void fprint(const std::string &filename) const {
        std::ofstream out(filename);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                out << a[i][j] << " ";
            }
            out << std::endl;
        }
        out << std::endl;
    }

    Matrix operator*(const Matrix &m) {
        Matrix res(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {
                    res.a[i][k] += a[i][j] * m.a[j][k];
                }
            }
        }
        return res;
    }

    Matrix transpose() {
        Matrix tr(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                tr.a[i][j] = a[j][i];
            }
        }
        return tr;
    }


    ~Matrix() {
        for (int i = 0; i < n; i++) {
            delete[] a[i];
        }
        delete[] a;
    }
};

int main(int argc, char **argv) {

    srand(time(nullptr));
    int n = (argc >= 2) ? atoi(argv[1]) : 20;
    std::string filename = (argc == 3) ? argv[2] : "test.txt";

    std::cout << "First param = size, second = filename" << std::endl;

    std::cout << "N = " << n << std::endl;

    Matrix A(n);
    std::cout << "Starting.." << std::endl;

    A.generate();

    std::cout << "Finished, matrix in file " << filename << std::endl;
    A.fprint(filename);


    return 0;
}


