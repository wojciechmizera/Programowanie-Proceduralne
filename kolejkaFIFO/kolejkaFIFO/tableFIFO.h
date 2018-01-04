#pragma once			// TODO make sure we can use 'pragma once' ...

#include "malloc.h"
#include "stdio.h"

namespace table
{

	struct Queue
	{
		int* table;
		int* first;
		int* last;
		int size;

		// Auxiliary value that changes inside Enqueu, Dequeue and is checked in qEmpty
		bool isFull;

		int key;
	};

	Queue* CreateQueue(int size);

	void ShowQueue(Queue* object);

	void Enqueue(Queue* table, int element);
	int Dequeue(Queue* table);
	int qEmpty(Queue* queue);
	void qClear(Queue* queue);
	void qRemove(Queue** queue);



	// Helpers
	void MoveFirstPointer(Queue** t);
	void MoveLastPointer(Queue** t);
}