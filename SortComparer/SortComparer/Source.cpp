#include "Header.h"

#define DEBUG_PRINT

#pragma region Utilites

// Copies a chunk of memory representing a table of integers
void CopyTable(int* pattern, int** destination, int size)
{
	*destination = (int*)malloc(size * sizeof(int));
	memcpy(*destination, pattern, sizeof(int) * size);
}


// Print the table 10 elements for a line
void ShowTable(int* table, int size)
{
	for (int i = 1; i < size + 1; i++)
	{
		printf("%d\t", *table++);
		if (!(i % 10)) printf("\n");
	}
}


// Create a table of random integers
void CreateTable(int size, int** table)
{
	*table = (int*)malloc(size * sizeof(int));
	memset(*table, 0, size * sizeof(int));

	srand((int)time(NULL));

	// auxiliary pointer to speed up filling the table 
	int* v = *table;
	for (int i = 0; i < size; i++)
		*v++ = rand() % 500;
}


// A function testing sorting algorithms
void Timer(void(*function[])(int* table, int size), int fSize, int* table, int tSize, char* names[])
{
	// Auxiliary table
	int* dummy = NULL;

	for (int i = 0; i < fSize; i++)
	{
		// Copy the table, so every algorithm has to deal with the same object
		CopyTable(table, &dummy, tSize);

		// Check time and sort the table
		time_t start = clock();
		function[i](dummy, tSize);

		// Calculate the time difference in miliseconds and convert it to seconds
		time_t stop = clock();
		double time = (double)(stop - start) / CLOCKS_PER_SEC;

		// Print name of function  and it's time
		printf("%-15s %lf\n", names[i], time);

		// Show a sample of sorted table
#ifdef DEBUG_PRINT
		printf("Sample: ");
		for (int i = 0; i < 20; i++)
			printf("%d, ", dummy[i]);
		printf("\n\n");
#endif
	}
}

#pragma endregion


#pragma region Sorting algorithms 

void InsertionSort(int* table, int size)		// ok
{
	for (int i = 1; i < size; i++)
	{
		int x = table[i];
		int j = i - 1;
		while (x < table[j])
			table[j + 1] = table[j--];

		table[j + 1] = x;
	}
}

void SelectionSort(int* table, int size)		// ok
{
	for (int i = 0; i < size - 1; i++)
	{
		int k = i;
		int x = table[i];
		for (int j = i + 1; j < size; j++)
			if (table[j] < x)
			{
				k = j;
				x = table[j];
			}

		table[k] = table[i];
		table[i] = x;
	}
}

void HalfSort(int* table, int size)				// ok
{
	for (int i = 1; i < size; i++)
	{
		int key = table[i];
		int left = 0;
		int right = i - 1;
		while (left <= right)
		{
			int middle = (left + right) / 2;
			if (key < table[middle])
				right = middle - 1;
			else
				left = middle + 1;
		}
		for (int j = i - 1; j >= left; --j)
			table[j + 1] = table[j];

		table[left] = key;
	}
}

void ShakeSort(int* table, int size)			// ok
{
	int bottom = 0;
	int top = size - 1;
	int temp;

	while (bottom < top)
	{
		for (int i = bottom; i < top; i++)
			if (table[i] > table[i + 1])
			{
				temp = table[i];
				table[i] = table[i + 1];
				table[i + 1] = temp;
			}

		top--;

		for (int i = top; i > bottom; i--)
			if (table[i] < table[i - 1])
			{
				temp = table[i];
				table[i] = table[i - 1];
				table[i - 1] = temp;
			}

		bottom++;
	}
}

// QuickSort, name changed for invoking function
void QSort(int*table, int left, int right)
{													// ok
	int i = left;
	int j = right;

	int x = table[(i + j) / 2];
	do
	{
		while (table[i] < x) i++;
		while (table[j] > x) j--;
		if (i <= j)
		{
			int temp = table[i];
			table[i++] = table[j];
			table[j--] = temp;

		}

	} while (i <= j);

	if (left < j)	QSort(table, left, j);
	if (right > i)	QSort(table, i, right);
}


// MergeSort, name changed for invoking function
void MrgSort(int* table, int left, int right)		// ok
{
	// i.e. till size of table == 1
	if (left != right)
	{
		int mid = (left + right) / 2;
		MrgSort(table, left, mid);
		MrgSort(table, mid + 1, right);
		Merge(table, left, mid, right);
	}
}

void Merge(int* table, int start, int mid, int end)
{
	int* temp = (int*)malloc((end - start + 1) * sizeof(int));
	memset(temp, 0, (end - start + 1) * sizeof(int));

	int i = start;
	int j = mid + 1;
	int k = 0;

	// Copy both series into one table
	while (i <= mid && j <= end)
	{
		if (table[j] < table[i])
			temp[k] = table[j++];

		else
			temp[k] = table[i++];

		k++;
	}

	// Return elements from temporary to original table
	if (i <= mid)
		while (i <= mid)
			temp[k++] = table[i++];
	else
		while (j <= end)
			temp[k++] = table[j++];

	// Copy the remaining elements
	for (i = 0; i <= end - start; i++)
		table[start + i] = temp[i];

	free(temp);

}


void MergeSortIter(int* table, int size)
{
	int* temp = (int*)malloc(size * sizeof(int));
	memset(temp, 0, size * sizeof(int));

	for (int k = 1; k < size; k *= 2)
	{
		for (int left = 0; left + k < size; left += k * 2)
		{
			int right = left + k;
			int rend = right + k;
			if (rend > size)
				rend = size;

			int m = left;
			int i = left;
			int j = right;

			// Copy serie
			while (i < right && j < rend)
			{
				if (table[i] <= table[j])
					temp[m] = table[i++];
				else
					temp[m] = table[j++];

				m++;
			}

			// Copy back
			while (i < right)
				temp[m++] = table[i++];

			while (j < rend)
				temp[m++] = table[j++];

			// Recopy remaining elements
			for (m = left; m < rend; m++)
				table[m] = temp[m];
		}
	}
	free(temp);
}


void HeapSort(int* table, int size)					// ok
{
	int right = size;
	Heapify(table, size);

	while (right > 1)
	{
		// Swap the Zero and Right element
		int swap = *table;
		*table = table[--right];
		table[right] = swap;

		Sift(table, right, 0);
	}
}


void Sift(int* table, int size, int l)
{
	int j = 2 * l + 1;
	int x = table[l];
	while (j < size)
	{
		if (j < size - 1)
			if (table[j] < table[j + 1])
				++j;
		if (x >= table[j])
			break;
		table[l] = table[j];
		l = j;
		j = 2 * l + 1; // sift
	}
	table[l] = x;
}

void Heapify(int* table, int size)
{
	int l = size / 2;
	while (l)
		Sift(table, size, --l);
}

#pragma endregion


#pragma region Miscellaneous

// A function testing recursive sorting algorithms
void TimerRecursive(void(*function[])(int* table, int left, int right), int fSize, int* table, int tSize, char* names[])
{
	// Auxiliary table
	int* dummy = NULL;

	for (int i = 0; i < fSize; i++)
	{
		// Copy the table, so every algorithm has to deal with the same object
		CopyTable(table, &dummy, tSize);

		// Check time and sort the table
		time_t start = clock();
		function[i](dummy, 0, tSize -1);

		// Calculate the time difference in miliseconds and convert it to seconds
		time_t stop = clock();
		double time = (double)(stop - start) / CLOCKS_PER_SEC;

		// Print name of function and it's time
		printf("%-15s %lf\n", names[i], time);

		// Show a sample of sorted table
#ifdef DEBUG_PRINT
		printf("Sample: ");
		for (int i = 0; i < 20; i++)
			printf("%d, ", dummy[i]);
		printf("\n\n");
#endif

	}
}


void merge(int* table, int left, int middle, int right)
{
	int n1 = middle - left + 1;
	int n2 = right - middle;

	// Create temp tables
	int* Left =  (int*)calloc(n1, sizeof(int));
	int* Right = (int*)calloc(n2, sizeof(int));

	// Copy data to temp tables
	for (int i = 0; i < n1; i++)
		Left[i] = table[left + i];
	for (int j = 0; j < n2; j++)
		Right[j] = table[middle + 1 + j];

	// Merge the temp arrays back into arr[l..r]
	int i = 0; // Initial index of first subarray
	int j = 0; // Initial index of second subarray
	
	while (i < n1 && j < n2)
	{
		if (Left[i] <= Right[j])
			table[left] = Left[i++];
		else
			table[left] = Right[j++];

		left++;
	}

	// Copy the remaining elements of Left, if thereare any
	while (i < n1)
		table[left++] = Left[i++];

	// Copy the remaining elements of Right, if there are any
	while (j < n2)
		table[left++] = Right[j++];

	free(Left);
	free(Right);
}


void mergeSort(int* table, int left, int right)
{
	if (left < right)
	{
		int middle = (left + right)/2;

		mergeSort(table, left, middle);
		mergeSort(table, middle + 1, right);

		merge(table, left, middle, right);
	}
}

#pragma endregion
