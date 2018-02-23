#ifndef _HEADER
#define _HEADER

#include <stdio.h>
#include <memory>	

// If uncommented prints a couple of control printouts
#define _DEBUG_PRINT

int CreateMatrix(double*** matrix, int size);

void ReadMatrix(int size, double ** matrix, FILE * file, double * vect);

void PrintMatrix(double** matrix, int size);

void InvertMatrix(double** matrixPtr, double** invertedPtr, int size);

double Determinant(double** matrix, int size);

void Multiply(double** matrix, double* vect, double* result, int size);

void DeleteMatrix(double*** table, int size);

#endif // !_HEADER

