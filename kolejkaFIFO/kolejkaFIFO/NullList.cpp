
#include "NullList.h"


namespace NullList
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
		object->head = object->tail = NULL;
		return object;
	}


	// Put an element at the end of the queue
	void Enqueue(Queue * object, int element)
	{
		Qitem* item = (Qitem*)calloc(1, sizeof(Qitem));
		if (!item)
		{
			printf("ERROR<Enqueue()>: Not enough memory\n");
			return;
		}
		item->key = element;

		if (!object->head)
		{
			object->head = object->tail = item;
		}
		else
		{
			object->tail->next = item;
			object->tail = item;
		}
	}


	// Get the first element from the queue
	int Dequeue(Queue * object)
	{
		// Make sure there is anything to do
		if (qEmpty(object))
		{
			// Must return a value thought
			printf("Error<Dequeue()>: Queue empty, returned 0\n");
			return 0;
		}

		int x = object->head->key;
		Qitem* q = object->head;
		object->head = object->head->next;
		free(q);

		return x;
	}


	// Return true if the queue is empty
	int qEmpty(Queue * list)
	{
		return !list->head;
	}


	// Clear the queue
	void qClear(Queue * list)
	{
		while (!qEmpty(list))
		{
			Dequeue(list);
		}
		list->head = list->tail = NULL;
	}


	// Delete the queue from memory
	void qRemove(Queue ** list)
	{
		qClear(*list);
		free(*list);
		*list = NULL;
	}


	// Prints the queue one element for a line
	void ShowQueue(Queue * object)
	{
		// Create an element to run along the queue
		Qitem* runner = object->head;

		while (runner != NULL)
		{
			printf("%d\n", runner->key);
			runner = runner->next;
		}
	}
}