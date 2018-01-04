#include "Header.h"


// 'Encapsulation' of the recursive functions so they fit in the table, might delay the execution of the algorithm, but it's more convenient this way
inline void MergeSort(int* table, int size)		
{ MrgSort(table, 0, size -1); }

inline void QuickSort(int* table, int size)
{ QSort(table, 0, size - 1); }


int main(int argc, char* argv[])
{

	if (argc != 2)
	{
		printf("Usage: %s <size of table>\n", argv[0]);
		return 1;
	}
	int size = atoi(argv[1]);
	
	int* table = NULL;
	CreateTable(size, &table);



	void(*wsk[])(int*, int) =	{  SelectionSort,	InsertionSort,   HalfSort,   ShakeSort,   QuickSort,   MergeSortIter,   MergeSort,   HeapSort  };
	char* names[] =				{ "SelectionSort", "InsertionSort" ,"HalfSort", "ShakeSort", "QuickSort", "MergeSortIter", "MergeSort", "HeapSort" };

	int nrOfFunctions = sizeof(names) / sizeof(char*);

	Timer(wsk, nrOfFunctions, table, size, names);


	// Explicitly invoking recursive algorithms
	
	//void(*wsk2[])(int*, int, int) =		{  MrgSort,   QSort};
	//char* names2[] =					{ "MrgSort", "QSort" };	
	//TimerRecursive(wsk2, 2, table, size, names2);

    return 0;
}

