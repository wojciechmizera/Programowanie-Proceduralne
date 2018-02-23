#include "listFIFO.h"


#include <iostream>
using namespace std;

namespace list
{
	// Creates an empty list
	Queue* CreateQueue()
	{
		Queue* object = (Queue*)calloc(1, sizeof(Queue));
		// If allocation was successcfull...
		if (!object)
		{
			printf("Error<CreateQueue()>: No memory avaliable\n");
			return NULL;
		}
		object->head = (Qitem*)malloc(sizeof(Qitem));
		object->tail = object->head;
		object->head->next = NULL;

		return object;
	}


	// Put an element at the end of the queue
	void Enqueue(Queue * object, int element)
	{
		// Create a new object
		Qitem* item = (Qitem*)calloc(1, sizeof(*item));
		if (!item)
		{
			printf("ERROR<Enqueue()>: Not enough memory\n");
		}

		item->key = element;
		object->tail->next = item;
		object->tail = item;
	}


	// Get the first element from the queue
	int Dequeue(Queue * list)
	{
		// Make sure there is anything to do
		if (qEmpty(list))
		{
			// Must return a value thought
			printf("Error<Dequeue()>: Queue empty, returned 0\n");
			return 0;
		}

		int x = list->head->next->key;
		Qitem* object = list->head;
		list->head = list->head->next;
		free(object);

		return x;
	}


	// Return true if the queue is empty
	int qEmpty(Queue * list)
	{
		return list->head == list->tail;
	}


	// Clear the queue
	void qClear(Queue * object)
	{
		while (!qEmpty(object))
		{
			Dequeue(object);
		}
	}


	// Delete the queue from memory
	void qRemove(Queue ** object)
	{
		qClear(*object);
		free(*object);
		*object = NULL;
	}


	// Helper function
	// Prints the queue one element for a line
	void ShowQueue(Queue * object)
	{
		// Create an element to run along the queue
		Qitem* runner = object->head;

		while (runner->next != NULL)
		{
			runner = runner->next;
			printf("%d\n", runner->key);
		}
	}
}
