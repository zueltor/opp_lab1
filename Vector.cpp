//
// Created by damir on 18.02.2020.
//

#include <fstream>
#include "Vector.h"

Vector::Vector(int size) : n(size), a(new double[size]) {
    for (int i = 0; i < n; i++) {
        a[i] = 0;
    }
}

Vector::Vector(int size, double val) : n(size), a(new double[size]) {
    for (int i = 0; i < n; i++) {
        a[i] = val;
    }
}

double &Vector::operator[](int i) {
    return a[i];
}

double Vector::operator[](int i) const {
    return a[i];
}

int Vector::size() const {
    return n;
}

void Vector::print(std::ostream &out) const {
    for (int i = 0; i < n; i++) {
        out << a[i] << std::endl;
    }
}

Vector::Vector(const Vector &v) {
    a = new double[v.n];
    n = v.n;
    for (int i = 0; i < n; i++) {
        a[i] = v.a[i];
    }
}

Vector &Vector::operator=(const Vector &v) {
    if (this != &v) {
        for (int i = 0; i < n; i++) {
            a[i] = v.a[i];
        }
    }
    return *this;
}

double *Vector::get_ptr() {
    return a;
}

double Vector::norm() {
    double res = 0.0;
    for (int i = 0; i < n; i++) {
        res += a[i] * a[i];
    }
    return sqrt(res);
}

double Vector::operator*=(const Vector &v) {
    double res = 0.0;
    for (int i = 0; i < n; i++) {
        res += a[i] * v.a[i];
    }
    return res;
}

Vector &Vector::operator*=(double d) {
    for (int i = 0; i < n; i++) {
        a[i] *= d;
    }
    return *this;
}

Vector &Vector::operator+=(const Vector &v) {
    for (int i = 0; i < n; i++) {
        a[i] += v.a[i];
    }
    return *this;
}

Vector &Vector::operator-=(const Vector &v) {
    for (int i = 0; i < n; i++) {
        a[i] -= v.a[i];
    }
    return *this;
}

Vector::~Vector() {
    delete[] a;
}

double operator*(Vector v1, const Vector &v2) {
    return v1 *= v2;
}

Vector operator+(Vector v1, const Vector &v2) {
    return v1 += v2;
}

Vector operator-(Vector v1, const Vector &v2) {
    return v1 -= v2;
}

Vector operator*(Vector v, double d) {
    return v *= d;
}
