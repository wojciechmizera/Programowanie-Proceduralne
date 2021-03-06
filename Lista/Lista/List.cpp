
#include <stdio.h>


#include "List.h"
#include "global.h"


// Creates a list
ListItem* MakeEmptyList()
{
	ListItem* list = (ListItem*)malloc(sizeof(ListItem));
	// If allocation was successfull...
	if (list)
		memset(list, 0, sizeof(ListItem));

	return list;
}


// Check if the list is empty
int isEmpty(ListItem* pList)
{
	return !(pList->pNext);
}


// Return the first element
ListItem* Front(ListItem* pList)
{
	return pList->pNext;
}


// Insert new element after specified segment 
void Insert(ListItem* pAfter, LISTINFO* pInfo)
{
	ListItem* p = (ListItem*)malloc(sizeof(ListItem));
	if (!p)
	{
		printf("Error<Insetr()>:Memory for object not allocated\n");
		return;
	}
	memset(p, 0, sizeof(ListItem));
	p->pInfo = pInfo;
	p->pNext = pAfter->pNext;
	pAfter->pNext = p;
}


// Insert as the first element...
void InsertFront(ListItem* pAfter, LISTINFO* pInfo)
{
	// ... and since head is the first element...
	Insert(pAfter, pInfo);
}


// Remove after specified pointer
void Remove(ListItem* pAfter)
{
	if (!isEmpty(pAfter))
	{
		ListItem* element = pAfter->pNext;
		pAfter->pNext = element->pNext;

		// Free allocated memory
		free(element->pInfo);
		free(element);
	}
	else
		printf("Remove: List empty\n");
}


// Remove the first element
void RemoveFront(ListItem* pAfter)
{
	// The same situation as with Insert()
	Remove(pAfter);
}


// Find element using extern comparing function
// summary: pList: List to check; x: element to find; pPrev: reference to pointer to the element before x; Comparer: pointer to a comparing function
ListItem* Find(ListItem* pList, const void* x, ListItem** pPrev, int(__cdecl *Comparer)(const void*, const void*))
{
	// Set pointer on the first element
	*pPrev = pList;
	ListItem* v = pList->pNext;
	// Untill *pPrev == NULL
	while (v)
	{
		// If the next element is what we are seeking, return it
		if (!Comparer(x, (v->pInfo)))
			return v;

		// Else check the next one
		*pPrev = v;

		v = v->pNext;
	}

	// If element not found, return NULL
	return *pPrev=NULL;
}


// Remove all elements and free the memory
void FreeList(ListItem* pList)
{
	// Helper pointer
	ListItem* jumper;

	while (!isEmpty(pList))
		RemoveFront(pList);
}


// Delete the list
void DelList(ListItem** pList)
{
	// First remove the elements
	FreeList(*pList);
	free(*pList);
	*pList = NULL;
}


// Sort the list using an extern Comparer function 
void SortList(ListItem* pList, int(__cdecl *Comparer)(const void*, const void*))
{
	// Set the first element
	ListItem* pFirst = pList;

	// Summary: Find minimum and set it as the first element, find next min and so on
	while (pFirst->pNext)
	{
		// Helper pointer to hold the minimum
		ListItem* pMin = pFirst;

		// Pointer to elements to compare with the min
		ListItem* jumper = pMin->pNext;

		// Check all elements untill NULL
		while (jumper->pNext)
		{
			// If needed, set new minimum
			if (Comparer(pMin->pNext->pInfo, jumper->pNext->pInfo) == 1)
				pMin = jumper;

			// Go to the next element
			jumper = jumper->pNext;
		}

		// Swap pointers if needed
		if (pFirst != pMin)
		{
			jumper = pMin->pNext->pNext;
			pMin->pNext->pNext = pFirst->pNext;
			pFirst->pNext = pMin->pNext;
			pMin->pNext = jumper;
		}

		// Go to the next element
		pFirst = pFirst->pNext;
	}
}
