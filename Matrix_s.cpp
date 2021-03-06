//
// Created by damir on 03.03.2020.
//

#include "Matrix_s.h"

void Matrix::fread(const std::string &filename) {
    std::ifstream is(filename);
    std::string s;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            is >> a[i][j];
        }
    }
    is.close();
}

Matrix::Matrix(int size) {
    a = new double *[size];
    n = size;
    for (int i = 0; i < size; i++) {
        a[i] = new double[size];
        for (int j = 0; j < n; j++) {
            a[i][j] = 0;
        }
    }
}

Vector Matrix::operator*(const Vector &v) {
    Vector res(v.size(), 0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            res[i] += a[i][j] * v[j];
        }
    }
    return res;
}


Matrix::~Matrix() {
    for (int i = 0; i < n; i++) {
        delete[] a[i];
    }
    delete[] a;
}
