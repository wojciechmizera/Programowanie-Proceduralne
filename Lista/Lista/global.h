#ifndef _GLOBAL
#define _GLOBAL

// Object stored in list
typedef struct
{
	int nKey;
} ListInfo;

typedef ListInfo* ListInfoPtr;

// Why not this way?
//typedef int x;

// Comparer function to define in main file
int Compare(const void*, const void*);

#endif // !_GLOBAL



