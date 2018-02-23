#pragma once		
#include "malloc.h"
#include "stdio.h"

namespace table
{

	typedef	struct
	{
		int* table;

		// Read and write indexes
		int first;
		int last;

		int maxSize;
		int size;
	} Queue;

	Queue* CreateQueue(int size);

	void ShowQueue(Queue* object);

	void QEnqueue(Queue* table, int element);
	int QDequeue(Queue* table);
	int QEmpty(Queue* queue);
	void QClear(Queue* queue);
	void QRemove(Queue** queue);


}