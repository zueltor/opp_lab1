#include <iostream>
#include "Matrix.h"
#include "Vector.h"

const double eps = 0.3e-5;

int main(int argc, char **argv) {

    int rank, size;
    int N = (argc >= 2) ? atoi(argv[1]) : 2048;


    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        std::cout << "Assuming matrix size = " << N << std::endl;
    }

    Vector u(N, 1);  //u=(1,1,...,1)
    MPIMatrix A(N, size, rank);

    std::string filename = (argc == 3) ? argv[2] : "test.txt";
    A.fread(filename);
    Vector b = A * u;
    Vector x(N, 0);
    Vector r = b - A * x;
    Vector z = r;
    double alpha;
    double beta;
    Vector r_prev(N);
    Vector tmp(N);
    int i = 0;
    double t1, t2;
    bool is_continue = false;
    MPI_Status st;

    t1 = MPI_Wtime();
    while (true) {
        //checking if condition is true to continue while
        //then send vector z to all processes
        if (rank == 0) {
            is_continue = r.norm() / b.norm() > eps;
            for (int j = 1; j < size; j++) {
                MPI_Send(&is_continue, 1, MPI_CXX_BOOL, j, 0, MPI_COMM_WORLD);
            }
            if (!is_continue) {
                break;
            } else {
                for (int j = 1; j < size; j++) {
                    MPI_Send(z.get_ptr(), z.size(), MPI_DOUBLE, j, 0, MPI_COMM_WORLD);
                }
            }
        } else {
            MPI_Recv(&is_continue, 1, MPI_CXX_BOOL, 0, 0, MPI_COMM_WORLD, &st);
            if (!is_continue) {
                break;
            } else {
                MPI_Recv(z.get_ptr(), z.size(), MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &st);
            }
        }

        tmp = A * z;    //***MPI multiplying***

        if (rank == 0) {
            alpha = (r * r) / (tmp * z);
            x = x + (z * alpha);
            r_prev = r;
            r = r - tmp * alpha;
            beta = (r * r) / (r_prev * r_prev);
            z = r + (z * beta);
            i++;
        }
    }
    t2 = MPI_Wtime();

    if (rank == 0) {
        std::cout << rank << ": number of iterations: " << i << std::endl;
        std::cout << rank << ": time = " << t2 - t1 << std::endl;
        std::cout << "result in result.txt\n";
        std::ofstream out("result.txt");
        x.print(out);
        out.close();
    }

    MPI_Finalize();

    return 0;
}