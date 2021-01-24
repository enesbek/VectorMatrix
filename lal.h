//
// Created by enesb on 15.01.2021.
//

#ifndef PROJE_LAL_H
#define PROJE_LAL_H

class Vector;

class Matrix {
protected:
    double *entries;
    int rows;
    int cols;

public:
    Matrix();
    Matrix(double *, int, int);
    virtual ~Matrix();
    void print();
    int getRow();
    int getCol();
    double *getEntries();
    double getNorm();

    Matrix operator+(const Matrix &a);
    Matrix operator-(const Matrix &a);
    Matrix operator*(const Matrix &a);
    Vector operator*(Vector &a);
    bool operator==(const Matrix &a);

    virtual void transpose();
    virtual void norm();
};

class Vector: public Matrix {
protected:
    double *entries;
    int rows;
    double l2norm;
public:
    Vector();
    Vector(double *, int);
    virtual ~Vector();
    void print();
    int getRow();
    double* getEntries();
    double getNorm();

    Vector operator+(const Vector &a);
    Vector operator-(const Vector &a);
    Vector operator*(const Vector &a);
    Vector operator*(Matrix &a);
    bool operator==(const Vector &a);
    Vector operator++();
    Vector operator++(int);
};

Vector **createVectorArray(int, int);
Matrix vectorArray2Matrix(Vector **, int, int);

#endif //PROJE_LAL_H
