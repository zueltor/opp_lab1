//
// Created by damir on 18.02.2020.
//

#ifndef LAB1_VECTOR_H
#define LAB1_VECTOR_H

#include <cmath>
#include <iostream>
#include <cstdlib>

class Vector {
    double *a;
    int n;
public:

    explicit Vector(int size);

    explicit Vector(int size, double val);

    double &operator[](int i);

    double operator[](int i) const;

    int size() const;

    void print(std::ostream &out) const;

    Vector(const Vector &v);

    Vector &operator=(const Vector &v);

    double *get_ptr();

    double norm();

    double operator*=(const Vector &v);

    Vector &operator*=(double d);

    Vector &operator+=(const Vector &v);

    Vector &operator-=(const Vector &v);

    ~Vector();
};

double operator*(Vector v1, const Vector &v2);

Vector operator+(Vector v1, const Vector &v2);

Vector operator-(Vector v1, const Vector &v2);

Vector operator*(Vector v, double d);


#endif //LAB1_VECTOR_H

