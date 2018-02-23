#include "Header.h"

#define DEBUG_PRINT

#pragma region Private Interface

// Utility helpers
void CopyTable(int* pattern, int** destination, int size);


// HeapSort helpers
void Update(int* table, int size, int l);


// MergeSort helpers
void Merge(int* table, int start, int mid, int end);


// MergeSortIter helpers
bool Copy(int* tab, int* temp, int nSize, int* i, int* ix);
void CopySerie(int* tab, int* temp, int nSize, int* i, int* ix);


// Recursive algorithms
void QSort(int*table, int left, int right);
void MrgSort(int* table, int left, int right);

#pragma endregion


#pragma region Utilites

// Copies a chunk of memory representing a table of integers
void CopyTable(int* pattern, int** destination, int size)
{
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
void Timer(Delegate func, int fSize, int* table, int tSize, const char* names[])
{
	int* dummy = (int*)malloc(tSize * sizeof(int));

	for (int i = 0; i < fSize; i++)
	{
		CopyTable(table, &dummy, tSize);

		// Sort copy of the table with time check
		time_t start = clock();
		func[i](dummy, tSize);
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
	free(dummy);
}

#pragma endregion


#pragma region Sorting algorithms 

void MergeSort(int* table, int size)		
{ MrgSort(table, 0, size -1); }


void QuickSort(int* table, int size)
{ QSort(table, 0, size - 1); }


void InsertionSort(int* table, int size)
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


void SelectionSort(int* table, int size)
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


void HalfSort(int* table, int size)
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


void ShakeSort(int* table, int size)
{
	int bottom = 0;
	int top = size - 1;
	int temp;
	int lastSwap;

	while (bottom < top)
	{
		for (int i = bottom; i < top; i++)
			if (table[i] > table[i + 1])
			{
				temp = table[i];
				table[i] = table[i + 1];
				table[i + 1] = temp;
				lastSwap = i;
			}

		top = lastSwap;

		for (int i = top; i > bottom; i--)
			if (table[i] < table[i - 1])
			{
				temp = table[i];
				table[i] = table[i - 1];
				table[i - 1] = temp;
				lastSwap = i;
			}

		bottom = lastSwap;
	}
}


void QSort(int*table, int left, int right)
{
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


void MrgSort(int* table, int left, int right)
{
	if (left != right)
	{
		int mid = (left + right) / 2;
		MrgSort(table, left, mid);
		MrgSort(table, mid + 1, right);
		Merge(table, left, mid, right);
	}
}


void Merge(int* table, int left, int mid, int right)
{
	int* t = (int*)malloc((right - left + 1) * sizeof(int));
	memcpy(t, table + left, (right - left + 1) * sizeof(int));

	int i = 0;
	int j = mid - left + 1;

	int q = left;

	while (i <= mid - left && j <= right - left)
	{
		if (t[i]<t[j])
			table[q++] = t[i++];
		else
			table[q++] = t[j++];
	}

	while (i <= mid - left) table[q++] = t[i++];

	free(t);
}


// Inefficient algorithm from Nicolaus Wirth's book
void MergeSortS(int* table, int nSize)
{
	int* temp1 = (int*)calloc(nSize, sizeof(int));
	int* temp2 = (int*)calloc(nSize, sizeof(int));
	int serie;
	do
	{
		int i = 0;
		int j = 0;
		int k = 0;
		while (i < nSize)
		{
			while ((i < nSize - 1) && (table[i] <= table[i + 1]))
				temp1[j++] = table[i++];
			if (i < nSize)
				temp1[j++] = table[i++];
			while ((i < nSize - 1) && (table[i] < table[i + 1]))
				temp2[k++] = table[i++];
			if (i < nSize)
				temp2[k++] = table[i++];
		}

		int end1 = j;
		int end2 = k;
		serie = 0;
		i = j = k = 0;
		while ((j < end1) && (k < end2))
		{
			bool end = false;
			while (!end)
			{
				if (temp1[j] <= temp2[k])
				{
					end = Copy(table, temp1, end1, &i, &j);
					if (end)
						CopySerie(table, temp2, end2, &i, &k);
				}
				else
				{
					end = Copy(table, temp2, end2, &i, &k);
					if (end)
						CopySerie(table, temp1, end1, &i, &j);
				}
			}
			serie++;
		}
		while (j < end1)
		{
			CopySerie(table, temp1, end1, &i, &j);
			serie++;
		}
		while (k < end2)
		{
			CopySerie(table, temp2, end2, &i, &k);
			serie++;
		}
	} while (serie > 1);

	free(temp1);
	free(temp2);
}


void CopySerie(int* table, int* temp, int size, int* i, int* ix)
{
	bool end = false;
	do
	{
		end = Copy(table, temp, size, i, ix);
	} while (!end);
}


bool Copy(int* table, int* temp, int size, int* i, int* ix)
{
	table[(*i)++] = temp[(*ix)++];
	if (*ix == size)
		return true;
	return (temp[*ix - 1] > temp[*ix]);
}


void HeapSort(int* table, int size)
{
	for(int i = size/2; i >= 0; i--)
		Update(table, i, size);

	for(int i = size - 1; i > 0; i--)
	{
		int swap = *table;
		*table = table[i];
		table[i] = swap;

		Update(table, 0, i);
	}
}


void Update(int* table, int left, int right)
{
	int j = 2 * left + 1;
	int x = table[left];
	while (j < right)
	{
		if (j < right - 1)
			if (table[j] < table[j + 1])
				++j;
		if (x >= table[j])
			break;
		table[left] = table[j];
		left = j;
		j = 2 * left + 1;
	}
	table[left] = x;
}

#pragma endregion

