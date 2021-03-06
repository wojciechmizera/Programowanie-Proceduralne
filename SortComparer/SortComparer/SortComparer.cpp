#include "Header.h"


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

	// Custom table resembling a delegate 
	Delegate func =		  {  SelectionSort,   InsertionSort,   HalfSort,   ShakeSort,   QuickSort,   MergeSortS,   MergeSort,   HeapSort };

	const char* names[] = { "SelectionSort", "InsertionSort", "HalfSort", "ShakeSort", "QuickSort", "MergeSortS", "MergeSort", "HeapSort" };

	int nrOfFunctions = sizeof(names) / sizeof(const char*);

	Timer(func, nrOfFunctions, table, size, names);

	free(table);





    return 0;
}
