//
// Created by damir on 18.02.2020.
//

#ifndef LAB1_P_MPIMATRIX_H
#define LAB1_P_MPIMATRIX_H


#include <string>
#include <fstream>
#include <iostream>
#include <mpi/mpi.h>
#include "Vector.h"

class MPIMatrix {
    double **a;
    int line_length;
    int num_processes;
    int rank;
    int num_lines;
    double *buff;
public:
    explicit MPIMatrix(int ls, int num_threads, int rank);

    void fread(const std::string &filename);

    Vector operator*(const Vector &v);

    ~MPIMatrix();
};


#endif //LAB1_P_MPIMATRIX_H
