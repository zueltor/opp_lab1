#include "Matrix_s.h"
#include "Vector.h"

const double eps = 0.3e-5;

int main(int argc, char **argv) {
    srand(time(nullptr));
    int rank, size;
    int N = (argc >= 2) ? atoi(argv[1]) : 2048;
    std::string filename = (argc == 3) ? argv[2] : "test.txt";
    Vector u(N, 1); //u=(1,1..,1)
    Matrix A(N);

    std::cout << "Assuming matrix size = " << N << std::endl;

    A.fread(filename.c_str());

    Vector b = A * u;
    Vector x(N, 0);

    Vector r = b - A * x;
    Vector z = r;
    double alpha;
    double beta;
    Vector tmp(N);
    Vector r_prev(N);
    int i = 0;
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    while (r.norm() / b.norm() > eps) {
        tmp = A * z;
        alpha = (r * r) / (tmp * z);
        x = x + (z * alpha);
        r_prev = r;
        r = r - tmp * alpha;
        beta = (r * r) / (r_prev * r_prev);
        z = r + (z * beta);
        i++;
    }

    clock_gettime(CLOCK_MONOTONIC, &end);

    std::cout << "time = " << end.tv_sec - start.tv_sec + 0.000000001 * (end.tv_nsec - start.tv_nsec) << std::endl;

    std::cout << "number of iterations: " << i << std::endl;

    std::cout << "result in result.txt\n";
    std::ofstream out("result.txt");
    x.print(out);
    out.close();

    return 0;
}