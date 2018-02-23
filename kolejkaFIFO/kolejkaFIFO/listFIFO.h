#pragma once			

#include <stdio.h>
#include <malloc.h>

namespace list
{
	typedef struct Qitem
	{
		Qitem* next;
		int key;
	} Qitem;


	typedef struct
	{
		Qitem* head;
		Qitem* tail;
	
	} Queue;

	Queue* CreateQueue();

	void Enqueue(Queue* list, int element);
	int Dequeue(Queue* list);
	int qEmpty(Queue* list);
	void qClear(Queue* list);
	void qRemove(Queue** list);

	// Helper function, prints actual content in the queue
	void ShowQueue(Queue* list);
}