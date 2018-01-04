#ifndef _LISTA_H
#define _LISTA_H

#include "global.h"
#include <memory>


typedef struct tagListItem
{
	// Information stored on the list
	ListInfoPtr pInfo;

	// Next element on the list
	tagListItem* pNext;
} ListItem;


ListItem* MakeEmptyList();
ListItem* Front(ListItem* pList);
ListItem* Find(ListItem* pList, const void*, ListItem** pPrev, int(__cdecl *comp)(const void*, const void*));

void Insert(ListItem* pAfter, ListInfoPtr pInfo);
void InsertFront(ListItem* pList, ListInfoPtr pInfo);
void Remove(ListItem* pAfter);
void RemoveFront(ListItem* pAfter);
void FreeList(ListItem* pList);
void DelList(ListItem** pList);
void SortList(ListItem* pList, int(__cdecl *comp)(const void*, const void*));

int isEmpty(ListItem*);

#endif // !_LISTA_H