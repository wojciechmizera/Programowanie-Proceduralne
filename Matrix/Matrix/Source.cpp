#include "Header.h"

// Private interface
void FillMinor(double ** minor, double ** matrix, int size, int row, int column);
void ComplementMatrix(double** matrix, double** complement, int size);
void Transpose(double** matrix, int size);


// Allocates memory for matrix
int CreateMatrix(double*** matrix, int size)
{
	*matrix = (double**)calloc(size, sizeof(double*));

	double** temp = *matrix;
	for (int i = 0; i < size; i++)
		*temp++ = (double*)calloc(size, sizeof(double));

	// If something went wrong return false
	if (matrix == NULL)	return 0;

	return 1;
}


// Read the file
void ReadMatrix(int size, double ** matrix, FILE * file, double * vect)
{
	for (int i = 0; i < size; i++)
	{
		// Auxiliary pointer
		double* v = *matrix++;

		for (int j = 0; j < size; j++, v++)
		{
			fscanf(file, "%lf", v);

			if (j == size - 1)
				fscanf(file, "%lf", vect++);
		}
	}
}


// Function multiplying matrix and vector
void Multiply(double** matrix, double* vect, double* result, int size)
{
	for (int i = 0; i < size; i++)
	{
		// Auxiliary pointers, renewing in each iteration
		double* pVect = vect;
		double* v = *matrix++;

		for (int j = 0; j < size; j++)
			*result += *v++ * *pVect++;

		result++;
	}
}


// Transpose a square matrix
void Transpose(double** matrix, int size)
{
	double** helper = matrix;

	for (int i = 0; i < size-1; i++)
	{
		double* pointer = *helper++ + i+1;
		for (int j = i; j < size; j++)
		{
			// First move the pointer outside the main diagonal, then start swapping
				double x = matrix[j][i];
				matrix[j][i] = *pointer;
				*pointer = x;
			*pointer++;
		}
	}
}


// Function printing matrix and vector
void PrintMatrix(double** matrix, int size)
{
	for (int i = 0; i < size; i++)
	{
		double* v = *matrix++;
		for (int j = 0; j < size; j++, v++)
			printf("%.3lf\t", *v);

		printf("\n");
	}
}


// Function inverting matrix (if possible)
void InvertMatrix(double** matrixPtr, double** invertedPtr, int size)
{
	// Step 1
	ComplementMatrix(matrixPtr, invertedPtr, size);


#ifdef _DEBUG_PRINT
	printf("Matrix of complements\n");
	PrintMatrix(invertedPtr, size);
	printf("\n");
#endif // !_DEBUG_PRINT


	// Step 2
	Transpose(invertedPtr, size);


#ifdef _DEBUG_PRINT
	printf("Transposed matrix of complements\n");
	PrintMatrix(invertedPtr, size);
	printf("\n");
#endif // !_DEBUG_PRINT


	double det = Determinant(matrixPtr, size);

	// Step 3
	for (int i = 0; i < size; i++)
	{
		double* inv = *invertedPtr++;
		for (int j = 0; j < size; j++)
			*inv++ *= 1 / det;
	}
}



double Determinant(double** matrix, int size)
{
	if (size == 1) return **matrix;

	double det = 0;

	// Imitate pow(-1, i+j)
	int multiplier = 1;

	// Create a minor
	double** minor = NULL;
	CreateMatrix(&minor, size - 1);

	// Set an auxiliary pointer to expand with respect to the first column
	double** word = matrix;

	for (int i = 0; i < size; i++)
	{
		// Fill the minor always with respect to the first column
		FillMinor(minor, matrix, size, i, 0);

		// LaPlace expansion
		det += **word++ * multiplier * Determinant(minor, size - 1);

		multiplier = -multiplier;
	}

	DeleteMatrix(&minor, size - 1);

	return det;
}


// Free memory allocated for a matrix
void DeleteMatrix(double*** table, int size)
{
	double** tab = *table;
	for (int i = 0; i < size; i++)
		free(*(tab + i));
	free(tab);
	*table = NULL;
}


// Fill minor matrix skipping specified row and column
void FillMinor(double ** minor, double ** matrix, int size, int currRow, int currColumn)
{
	for (int row = 0; row < size; row++, matrix++)
	{
		if (currRow == row) continue;

		double* minorPtr = *minor++;
		double*  matrixPtr = *matrix;

		for (int column = 0; column < size; column++, matrixPtr++)
		{
			if (column == currColumn) continue;

			*minorPtr++ = *matrixPtr;
		}
	}
}


// Fill matrix of complements for inverting purposes
void ComplementMatrix(double** matrix, double** complement, int size)
{
	double** minor = NULL;

	if (!CreateMatrix(&minor, size - 1))
	{
		printf("No memory avaliable\n");
		return;
	}

	// Imitate pow(-1, i+j)
	//int multiplier = 1;

	double** helper = complement;

	for (int row = 0; row < size; row++)
	{
		int multiplier = (row%2) ? -1 : 1;

		double* pointer = *helper++;
		for (int column = 0; column < size; column++)
		{
			// Fill minor for determinant
			FillMinor(minor, matrix, size, row, column);

			// Key line
			*pointer++ = multiplier * Determinant(minor, size - 1);

			multiplier = -multiplier;
		}
	}
	// Clean up after yourself
	DeleteMatrix(&minor, size - 1);
}