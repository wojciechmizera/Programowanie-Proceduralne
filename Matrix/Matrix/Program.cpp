// Matrix.cpp : Defines the entry point for the console application.
//


#include "Header.h"


int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		printf("Usage: <%s> <dataFile>\n", argv[0]);
		// ERROR_BAD_ARGUMENTS
		return 160;
	}

	FILE *file = NULL;

	if ((file = fopen(argv[1], "rt")) == NULL)
	{
		printf("Failed to open specified file\n");
		// ERROR_FILE_NOT_FOUND
		return 2;
	}

	int size;

	fscanf(file, "%d", &size);

	double** matrix = NULL;
	double** inverted = NULL;
	double* vect = (double*)calloc(size, sizeof(double));

	if (!CreateMatrix(&matrix, size) || !CreateMatrix(&inverted, size))
	{
		printf("Memory not allocated!\n");
		// ERROR_NOT_ENOUGH_MEMORY
		return 8;
	}

	ReadMatrix(size, matrix, file, vect);

	fclose(file);

#ifdef _DEBUG_PRINT
	printf("Matrix read form file\n");
	PrintMatrix(matrix, size);
	printf("\n");
	printf("\Vector read from file\n");
	double* temp = vect;
	for (int i = 0; i < size; i++) printf("%0.3lf\t", *temp++);
	printf("\n\n");
#endif // !_DEBUG_PRINT

	if (Determinant(matrix, size) < 1e-10)
	{
		printf("Determinant = 0, unable to invert matrix\n");
		return 1;
	}

	InvertMatrix(matrix, inverted, size);

#ifdef _DEBUG_PRINT
	printf("Inverted matrix\n");
	PrintMatrix(inverted, size);
	printf("\n");
#endif // !_DEBUG_PRINT

	double* result = (double*)calloc(size, sizeof(double));

	Multiply(inverted, vect, result, size);

	double* r = result;
	for (int i = 0; i < size; i++)
		printf("x%d = %.3lf\n", i, *r++);

	free(vect);
	free(result);
	vect = result = NULL;
	DeleteMatrix(&matrix, size);
	DeleteMatrix(&inverted, size);

	return 0;
}


