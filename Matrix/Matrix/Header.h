#ifndef _HEADER
#define _HEADER

#include <stdio.h>
#include <memory>	



int GetMatrix(FILE* file, double*** matrix, double** vect, int size);

void ReadMatrix(int size, double ** matrix, FILE * file, double * vect);

void Transpose(double** matrix, int size);

void PrintMatrix(double** matrix, double* vect, int size);

double CalculateDet(int n, int * WK, double ** A, int w = 0);

double** InvertMatrix(double** matrix, int size);

double Determinant(double** matrix, int size);

double* Multiply(double** matrix, double* vect, int size);

void DeleteMatrix(double*** table, int size);



#endif // !_HEADER




