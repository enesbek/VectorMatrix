//
// Created by enesb on 16.01.2021.
//
#include <iostream>
#include <string>
#include <math.h>
#include "lal.h"
using namespace std;

Matrix::Matrix(double *dptr, int x, int y) {
    this->entries = dptr;
    this->rows = x;
    this->cols = y;
}

Vector::Vector(double *dptr, int x) : Matrix(dptr, x, x) {
    rows = x;
    entries = dptr;
    double a = 0;
    int i;
    for(i = 0; i < x; i++){
        a += this->entries[i] * this->entries[i];
    }
    l2norm = sqrt(a);
}

Matrix::~Matrix(){
    delete this->entries;
}

Vector::~Vector(){
    delete this->entries;
}

void Matrix::print() {
    int i, j;
    for(i = 0; i < this->rows; i++) {
        for (j = 0; j < this->cols; j++)
            cout << entries[(i * cols) + j] << " ";
        cout << endl;
    }
    cout << "--------------"<<endl;
}

void Vector::print() {
    int i;
    for(i = 0; i < this->rows; i++)
        cout << this->entries[i] << " ";
    cout << endl;
    printf("L2norm: %.5f", this->l2norm);
    cout << endl;
}

Matrix Matrix::operator+(const Matrix &a){

    int maxElement = this->rows * this->cols;
    double *entries = (double *)calloc(maxElement, sizeof(double));

    if(this->rows == a.rows && this->cols == a.cols){
        int i;
        for(i = 0; i < maxElement; i++)
            entries[i] = this->entries[i] + a.entries[i];
    }
    else
        cout << "Invalid operation. Size mismatch!" << endl;

    Matrix sumMatrix(entries, this->rows, this->cols);
    return sumMatrix;
}

Vector Vector::operator+(const Vector &a) {
    double *entries = (double *)calloc(a.rows, sizeof(double));

    if(this->rows == a.rows){
        int i;
        for (i = 0; i < a.rows; i++)
            entries[i] = a.entries[i] + this->entries[i];
    }
    else
        cout << "Invalid operation. Size mismatch!" << endl;

    Vector sum(entries, a.rows);
    return sum;
}

Matrix Matrix::operator-(const Matrix &a) {

    int maxElement = this->rows * this->cols;
    double *entries = (double *)calloc(maxElement, sizeof(double));

    if(this->rows == a.rows && this->cols == a.cols){
        int i;
        for(i = 0; i < maxElement; i++)
            entries[i] = this->entries[i] - a.entries[i] ;
    }
    else
        cout << "Invalid operation. Size mismatch!" << endl;

    Matrix subtractMatrix(entries, this->rows, this->cols);
    return subtractMatrix;
}

Vector Vector::operator-(const Vector &a) {

    double *entries = (double *)calloc(a.rows, sizeof(double));

    if(this->rows == a.rows){
        int i;
        for(i = 0; i < a.rows; i++)
            entries[i] = this->entries[i] - a.entries[i];
    }
    else
        cout << "Invalid operation. Size mismatch!" << endl;

    Vector subtractVector(entries, a.rows);
    return subtractVector;
}

//matrix * matrix
Matrix Matrix::operator*(const Matrix &a) {
    double *entries = (double *)calloc(this->rows * a.cols, sizeof(double));

    if(this->cols == a.rows){
        int i, j, k;
        int count = 0;
        for(i = 0; i < this->rows; i++)
            for(j = 0; j < a.cols; j++) {
                for (k = 0; k < this->cols; k++)
                    entries[count] += this->entries[i * this->cols + k] * a.entries[a.cols * k + j];
                count++;
            }
    }
    else
        cout << "Invalid operation. Size mismatch!" << endl;

    Matrix multiMatrix(entries, this->rows, a.cols);
    return multiMatrix;
}

int Vector::getRow() {return this->rows;}

double* Vector::getEntries(){return this->entries;}

//vector * vector
Vector Matrix::operator*(Vector &a) {
    double *entries = (double *) calloc(this->rows, sizeof(double));
    if(a.getRow() == this->cols) {
        int counter = 0;
        double multi = 0;
        int i, j;
        for (i = 0; i < this->rows; i++) {
            entries[counter] = 0;
            for (j = 0; j < this->cols; j++)
                multi += (double) (a.getEntries()[j] * this->entries[j + i * this->cols]);
            *(entries + counter) = (double) multi;
            multi = 0;
            counter++;
        }
    }
    else
        cout << "Invalid operation. Size mismatch!" << endl;

    Vector multiVector(entries, this->rows);
    return multiVector;
}

int Matrix::getRow() {return this->rows;}

int Matrix::getCol() {return this->cols;}

double* Matrix::getEntries() {return this->entries;}

//vector * Matrix
Vector Vector::operator*(Matrix &a) {
    double *entries = (double*) calloc(a.getRow(), sizeof(double));
    if(a.getRow() == this->rows){
        int counter = 0;
        double multi = 0;
        int i, j;
        for(i = 0; i < a.getRow(); i++){
            entries[counter] = 0;
            for(j = 0; j < a.getCol(); j++)
                multi += (double)( this->entries[j] * a.getEntries()[j + i * a.getCol()]);
            *(entries + counter) = (double) multi;
            multi = 0;
            counter++;
        }
    }
    else
        cout << "Invalid operation. Size mismatch!" << endl;

    Vector multiVector(entries, a.getRow());
    return multiVector;
}

//vector x vector
Vector Vector::operator*(const Vector &a) {
    double *entries = (double*) calloc(a.rows, sizeof(double));
    if (this->rows == a.rows) {
        int i;
        for (i = 0; i < this->rows; i++)
            entries[i] = this->entries[i] * a.entries[i];
    }
    else
        cout << "Operation is invalid. Incompatible lengths." << endl;

    Vector multiVector(entries, a.rows);
    return multiVector;
}


bool Matrix::operator==(const Matrix &a){
    bool isEqual = true;
    if(this->rows == a.rows && this->cols == a.cols){
        int i;
        for(i = 0; i < this->rows * this->cols; i++){}
            if(this->entries[i] != a.entries[i])
                isEqual = false;
    }
    else
        isEqual = false;

    return isEqual;
}

bool Vector::operator==(const Vector &a){
    bool isEqual = true;
    if(this->rows == a.rows){
        int i;
        for(i = 0; i < this->rows; i++){}
        if(this->entries[i] != a.entries[i])
            isEqual = false;
    }
    else
        isEqual = false;

    return isEqual;
}


Vector Vector::operator++(){
    int i;
    for(i = 0; i < this->rows; i++)
        this->entries[i]++;
    cout << "Pre-increment is done." << endl;
    return *this;
}

Vector Vector::operator++(int) {
    const Vector before(this->entries, this->rows);
    int i;
    for(i = 0; i < this->rows; i++)
        ++*(before.entries + i);
    cout << "Post-increment is done." << endl;
    return before;
}


void Matrix::transpose() {

    if(typeid(*this).name() == typeid(Vector).name()){
        cout << "Transpose operation do not make difference in Vectors!" << endl;
        cout << "Because of that, I'm just printing transpose Vector as vertically in this function!" << endl;
        int i;
        for(i = 0; i < this->rows; i++)
            cout << this->entries[i] << endl;
    }
    else{
        double *entries = (double *)calloc(this->rows * this->cols, sizeof(double));
        int i, j, k;
        for(i = 0; i < this->rows; i++) {
            for (j = 0; j < this->cols; j++) {
                int index1 = i * this->cols + j;
                int index2 = j * this->rows + i;
                entries[index2] = this->entries[index1];
            }
        }
        this->entries = entries;
        int temp = this->rows;
        this->rows = this->cols;
        this->cols = temp;
    }
    cout << "Transpose operation is done." << endl;
}


double Vector::getNorm() {return this->l2norm;}

void Matrix::norm(){
    double norm;
    if(typeid(*this).name() == typeid(Vector).name()){
        norm = dynamic_cast<Vector *>(this)->getNorm();
    }
    else{
        double l2norm = 0;
        int i;
        for (i = 0; i < this->rows * this->cols; i++)
            l2norm +=pow(entries[i], 2);
        norm = sqrt(l2norm);
    }
    cout << norm << endl;
}


Vector **createVectorArray(int m, int p){
    Vector **vectorArray = (Vector **)calloc(m, sizeof(Vector*));
    int i, j;
    for(i = 0; i < m; i++)
        vectorArray[i] = (Vector *)calloc(p, sizeof(Vector));
    for(i = 0; i < m; i++){
        double *entries = (double *)calloc(p, sizeof(double));
        for(j = 0; j < p; j++)
            entries[j] = (double) rand() / (double) (RAND_MAX) + 1.0;
        vectorArray[i] = new Vector(entries, p);
    }

    return vectorArray;
}


Matrix vectorArray2Matrix(Vector **vectorArray, int m, int p){
    double *entries = (double *)calloc(m * p, sizeof(double));
    int i, j;
    for (i = 0; i < m; ++i)
        for (j = 0; j < p; j++)
            entries[i + j * m] = vectorArray[i]->getEntries()[j];

    Matrix matrix(entries, p, m);
    return matrix;
}

Matrix::Matrix(){
    double* entries = (double*) calloc(1,sizeof(double));
    this->entries = entries;
}


























