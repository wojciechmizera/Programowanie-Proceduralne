#pragma once			// Make sure we can use 'pragma once'...

#include <stdio.h>
#include <malloc.h>

namespace list
{

	struct Queue
	{
		Queue* head;
		Queue* tail;
		Queue* next;

		int key;
	};

	Queue* CreateQueue();

	void ShowQueue(Queue* list);

	void Enqueue(Queue* list, int element);
	int Dequeue(Queue* list);
	int qEmpty(Queue* list);
	void qClear(Queue* list);
	void qRemove(Queue** list);




}