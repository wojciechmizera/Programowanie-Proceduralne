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
		if (object)
		{
			object->head = object->tail = object;
			object->next = NULL;
			return object;
		}
		printf("Error<CreateQueue()>: No memory avaliable\n");
		return NULL;
	}

	// Prints the queue one element for a line
	void ShowQueue(Queue * object)
	{
		// Create an element to run along the queue
		Queue* runner = object->head;

		while (runner->next != NULL)
		{
			printf("%d\n", runner->key);
			runner = runner->next;
		}
	}


	// Put an element at the end of the queue
	void Enqueue(Queue * object, int element)
	{
		// Create a new object
		Queue* _new = CreateQueue();

		// Do the job with the last element  
		object->tail->key = element;
		object->tail->next = _new;
		object->tail = _new;
		_new->head = object->head;
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

		int x = list->head->key;
		Queue* object = list->head;

		list->head = list->head->next;
		return x;
	}


	// Return true if the queue is empty
	int qEmpty(Queue * list)
	{
		return list->head == list->tail;
	}


	// Clear the queue
	void qClear(Queue * list)
	{
		while (!qEmpty(list))
		{
			Dequeue(list);
		}
	}


	// Delete the queue from memory
	void qRemove(Queue ** list)
	{
		qClear(*list);
		free(*list);
		*list = NULL;
	}
}
