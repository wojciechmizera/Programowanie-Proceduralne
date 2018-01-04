// Matrix.cpp : Defines the entry point for the console application.
//


#include "Header.h"


// If uncommented prints a couple of control printouts
//#define _DEBUG_PRINT

int main(int argc, char* argv[])
{

	if (argc != 2)
	{
		printf("Usage: <%s> <dataFile>\n", argv[0]);
		// ERROR_BAD_ARGUMENTS
		return 160;
	}

	FILE *file;

	if ((file = fopen(argv[1], "r")) == NULL)
	{
		printf("Failed to open specified file");
		// ERROR_FILE_NOT_FOUND
		return 2;
	}

	int size;
	double** matrix = NULL;
	double* vect = NULL;

	fscanf(file, "%d", &size);


	// Step 1: Get matrix from file
	if (GetMatrix(file, &matrix, &vect, size))
	{
		printf("Memory not allocated!");
		// ERROR_NOT_ENOUGH_MEMORY
		return 8;
	}

	fclose(file);

#ifdef _DEBUG_PRINT
	printf("DATA READ:\nsize: %d\n", size);
	
	PrintMatrix(matrix, vect, size);

	printf("\nDeterminant: %lf\n", Determinant(matrix, size));
#endif

	// Step 2: Invert matrix
	matrix = InvertMatrix(matrix, size);

#ifdef _DEBUG_PRINT
	printf("\nAfter inverting:\n");

	PrintMatrix(matrix, vect, size);
#endif

	// Step 3: Solve system of equations
	double* res = Multiply(matrix, vect, size);

	for (int i = 0; i < size; i++)
		printf("x%d = %.3lf\n", i, res[i]);


	
	for (int i = 0; i < size; i++)
		free(*(matrix + i));

	free(matrix);
	free(vect);
	free(res);

	matrix = NULL;
	vect = res = NULL;

	return 0;
}
