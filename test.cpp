#include <iostream>
#include "lal.h"
using namespace std;

int main() {

    double array3[] = {1,2,3, 4};
    Matrix newMatrix(array3, 2, 2);
    newMatrix.print();
    double array4[] = {5,6,7,8};
    Matrix newMatrix2(array4, 2, 2);
    newMatrix2.print();
    newMatrix = newMatrix * newMatrix2;
    newMatrix.print();
    newMatrix.transpose();
    newMatrix.print();
    newMatrix.norm();


    double array[] = {1, 2, 3, 4};
    Vector newVector(array, 4);
    newVector.print();
    newVector.norm();
    newVector.transpose();
    double array2[] = {5, 6, 7, 8};
    Vector newVector2(array2, 4);
    newVector = newVector + newVector2;
    newVector.print();
    newVector = newVector - newVector2;
    newVector.print();
    newVector = newVector * newVector2;
    newVector.print();


    Matrix arr[4];
    arr[0] = newVector;
    arr[1] = newVector2;
    arr[2] = newMatrix;
    arr[3] = newMatrix2;
    arr[2].print();
    arr[3].print();




    return 0;
}
