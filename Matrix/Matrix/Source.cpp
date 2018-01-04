#include "Header.h"

// If uncommented matrix is printed after each function
//#define _DEBUG_PRINT

// Allocates memory and reads matrix from specified file
int GetMatrix(FILE* file, double*** matrix, double** vect, int size)
{
	// Allocate memory for matrix and vector
	*matrix = (double**)calloc(size, sizeof(double*));
	*vect = (double*)calloc(size, sizeof(double));

	double** temp = *matrix;
	for (int i = 0; i < size; i++)
		*temp++ = (double*)calloc(size, sizeof(double));

	// If something went wrong return error code 
	if (matrix == NULL || vect == NULL)	return 1;

	// If memory allocated, read from file
	ReadMatrix(size, *matrix, file, *vect);

	// 
	return 0;

#ifdef _DEBUG_PRINT
	printf("w getmatrix:\n");

	PrintMatrix(matrix, vect, size);
#endif

}

// A separate function to read matrix, used in GetMatrix(...)
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
double* Multiply(double** matrix, double* vect, int size)
{
	// Allocate memory for result vector and set values to 0
	double* res = (double*)calloc(size, sizeof(double));

	// Auxiliary pointer
	double* pointer = res;

	for (int i = 0; i < size; i++)
	{
		// Auxiliary pointers, renewing in each iteration
		double* pVect = vect;
		double* v = *matrix++;			

		// Multiplication
		for (int j = 0; j < size; j++)
			*pointer += (*v++ * (*pVect++));

		// Move to next cell of the result table
		pointer++;
	}
#ifdef _DEBUG_PRINT
	printf("in function Multiply()\n");
	for (int i = 0; i < size; i++)
		printf("%lf\n",res[i]);

#endif

	return res;
}


// Transposing function, not used...
void Transpose(double** matrix, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = i + 1; j < size; j++)
		{
			matrix[i][j] -= matrix[j][i];
			matrix[j][i] += matrix[i][j];
			matrix[i][j] = matrix[j][i] - matrix[i][j];
		}
	}
}  


// Function printing matrix and vector
void PrintMatrix(double** matrix, double* vect, int size)
{
	for (int i = 0; i < size; i++)
	{
		double* v = *matrix++;
		for (int j = 0; j < size; j++, v++)
		{
			printf("%.3lf\t", *v);

			if (j == size - 1)
				printf("|\t %.3lf", *vect++);
		}
		printf("\n");
	}
}


// Function inverting matrix (if possible)
double** InvertMatrix(double** matrix, int size)
{
	// Matrix 1x1 stays the same
	if (size == 1) return matrix;

	// Calculate the determinant and check if it's not 0, if so return NULL
	double det = Determinant(matrix, size);

	if (!det)
	{
		printf("Determinant = 0, Cannot invert matrix!");
		return NULL;
	}

	// Allocate memory for future operations
	double** resMatrix = NULL;
	double** minor = NULL;
	int* WKtemp = NULL;

	resMatrix = (double**)calloc(size, sizeof(double*));
	minor = (double**)calloc(size - 1, sizeof(double*));
	WKtemp = (int*)calloc(size - 1, sizeof(int));


	// Check the allocation result after every step and if something went wrong return NULL 
	if(!resMatrix || !minor || !WKtemp)
		return 0;

	for (int i = 0; i < size; i++)
	{
		*(resMatrix + i) = (double*)calloc(size, sizeof(double));
		if (!(resMatrix + i)) return 0;
	}

	for (int i = 0; i < size - 1; i++)
	{
		*(minor + i) = (double*)calloc(size - 1, sizeof(double));
		if (!(minor + i)) return 0;
	}

	// Helper pointer
	int* p = WKtemp;

	// If everything went well up to now fill the column vector
	for (int i = 0; i < size - 1; *p++= i++);

	// Imitating (-1)^(i+j), so we will be multiplying by 1 and -1 for a change
	int m = 1;

	// Fill the minors and calculate determinants all in one loop
	// These two loops for the result matrix
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
		{
			int c = 0;
			// These two loops for the minor
			for (int a = 0; a < size - 1; a++)
			{
				// Skip current row
				if (i == a) c++;
				int d = 0;

				for (int b = 0; b < size - 1; b++)
				{
					// Skip current column
					if (j == b) d++;
					
					// Filling minor for Determinant() function
					minor[a][b] = matrix[c][d];
					d++;
				}
				c++;
			}
			// Filling the result matrix with determinants of minors
			// ... and avoiding separate transposing function just by inverting indexes
			*(*(resMatrix+j)+i) = 1 / det * m * CalculateDet(size - 1, WKtemp, minor);

			// Change 1 to -1, or -1 to 1
			m = -m;
		}
	
	// Clean up after yourself
	DeleteMatrix(&minor, size - 1);
	free(WKtemp);
	WKtemp = NULL;

	return resMatrix;
}


// Function calculating determinant of a matrix
double Determinant(double** matrix, int size)
{
	int *colVect = (int*)malloc(size*sizeof(int));

	int* tempVect = colVect;

	// Fill the colVect with subsequent numbers
	for (int i = 0; i < size; *(tempVect++) = i++);

	// Invoke Laplace expansion
	double det = CalculateDet(size, colVect, matrix);

	free(colVect);

	return det;
}


// Recursive Laplace expansion function
double CalculateDet(int size, int * colVect, double ** matrix, int w)
{
	double result = 0;

	// Basically, return the only element of 1x1 matrix
	if (size == 1)
		return *(*(matrix + w) + *colVect);

	else
	{
		int *tempColVect = (int*)malloc((size -1) * sizeof(int));

		// Imitating (-1)^(i+j), so we will be multiplying by 1 and -1 for a change
		int m = 1;

		for (int i = 0; i < size; i++)
		{
			int k = 0;

			for (int j = 0; j < size - 1; j++)
			{
				// Skip current column
				if (k == i)
					k++;
				// Cannot use v = tempColVect++, due to the later use of tempColVect, same with colVect and matrix
				*(tempColVect + j) = *(colVect + k++);
			}
			// Laplace expansion
			result += m * *(*(matrix + w) + *(colVect + i)) * CalculateDet(size - 1, tempColVect, matrix, w + 1);
			
			// Change 1 to -1, or -1 to 1
			m = -m;
		}

		free(tempColVect);

		return result;
	}
}


// Free memory allocated for a matrix
void DeleteMatrix(double*** table, int size)
{
	double** tab = *table;
	for (int i = 0; i < size - 1; i++)
		free(*(tab + i));
	free(tab);
	*table = NULL;
}