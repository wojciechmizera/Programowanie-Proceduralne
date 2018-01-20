// Lista.cpp: Defines an entry point for the console application.
//

#include <stdio.h>

#include "List.h"
#include "global.h"

// Constant representing nr of columns; to be used inside of PrintList function
#define COLS 4

// Print the list
void PrintList(ListItem* pList);


int main(int argc, char* argv[])
{
	ListItem* pList = MakeEmptyList();


	for (int i = 0; i < 20; i++)
	{
		LISTINFO* x = (LISTINFO*)malloc(sizeof(ListInfo));
		x->nKey = i + 7;
		InsertFront(pList, x);
	}


	PrintList(pList);


	printf("\n");
	LISTINFO* x = (LISTINFO*)malloc(sizeof(ListInfo));
	x->nKey = 14;
	ListItem* pPrev = NULL;

	RemoveFront(Find(pList, x, &pPrev, Compare));
	PrintList(pList);

	printf("\n\n");
	InsertFront(Find(pList, x, &pPrev, Compare), x);

	SortList(pList, Compare);
	
	PrintList(pList);
	
	DelList(&pList);

	printf("After deleting list pointer is set to %d\n", pList);

	return 0;
}



// Function printing the list
void PrintList(ListItem* pList)
{
	// Helper element to run along the list
	ListItem* jumper = Front(pList);
	int i = 1;

	// Keep printing untill jumper == NULL
	while (jumper)
	{
		// Due to %d only integers and chars will work...
		printf("%d\t", jumper->pInfo->nKey);

		// New line every couple of elements
		if (i++ % COLS == 0)
			printf("\n");

		jumper = jumper->pNext;
	}
}


// Comparer used for sorting purposes
// To introduce some type control void* pointers could be replaced by LISTINFO*
int Compare(const void* pFirst, const void* pNext)
{
	if (((LISTINFO*)pFirst)->nKey > ((LISTINFO*)pNext)->nKey)
		return 1;
	if (((LISTINFO*)pFirst)->nKey == ((LISTINFO*)pNext)->nKey)
		return 0;
	return -1;
}