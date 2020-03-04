//
// Created by damir on 03.03.2020.
//

#ifndef FINAL_LAB1_MATRIX_S_H
#define FINAL_LAB1_MATRIX_S_H

#include <string>
#include <fstream>
#include <iostream>
#include "Vector.h"

class Matrix {
    double **a;
    int n;
public:
    explicit Matrix(int size);

    void fread(const std::string &filename);

    Vector operator*(const Vector &v);

    ~Matrix();
};


#endif //FINAL_LAB1_MATRIX_S_H
