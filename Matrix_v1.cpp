п//
// Created by damir on 18.02.2020.
//

#include "Matrix.h"

MPIMatrix::MPIMatrix(int ls, int num_threads, int rank) {
    line_length = ls;
    num_processes = num_threads;
    this->rank = rank;
    buff = new double[line_length];
    num_lines = (rank != num_threads - 1) ? line_length / num_processes : line_length / num_processes +
                                                                          line_length % num_processes;
    a = new double *[num_lines];
    for (int i = 0; i < num_lines; i++) {
        a[i] = new double[line_length];
        for (int j = 0; j < line_length; j++) {
            a[i][j] = 0;
        }
    }
}

void MPIMatrix::fread(const std::string &filename) {
    std::ifstream is(filename);
    std::string s;
    int line = line_length / num_processes * rank;

    for (int i = 0; i < line; i++) {
        std::getline(is, s);
    }

    for (int i = 0; i < num_lines; i++) {
        for (int j = 0; j < line_length; j++) {
            is >> a[i][j];
        }
    }
    is.close();
}

Vector MPIMatrix::operator*(const Vector &v) {
    Vector res(v.size(), 0);

    for (int i = 0; i < num_lines; i++) {
        for (int j = 0; j < line_length; j++) {
            res[i] += a[i][j] * v[j];
        }
    }

    MPI_Status st;

    int *recvcounts = new int[num_processes];  //set up for gatherv
    int *displs = new int[num_processes];
    displs[0] = 0;
    for (int i = 0; i < num_processes - 1; i++) {
        recvcounts[i] = line_length / num_processes;
        displs[i + 1] = displs[i] + recvcounts[i];
    }
    recvcounts[num_processes - 1] = line_length/num_processes + line_length % num_processes;


    MPI_Gatherv(res.get_ptr(), num_lines, MPI_DOUBLE, buff, recvcounts,displs,MPI_DOUBLE,0,MPI_COMM_WORLD);

    if (rank == 0) {
        for (int i = 0; i < v.size(); i++) {
            res[i] = buff[i];
        }
    }

    return res;
}

MPIMatrix::~MPIMatrix() {
    for (int i = 0; i < num_lines; i++) {
        delete[] a[i];
    }
    delete[] a;
    delete[] buff;
}

