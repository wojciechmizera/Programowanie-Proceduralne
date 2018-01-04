
#include "NullList.h"
#include <iostream>
using namespace std;


namespace NullList
{
	// Creates an empty list
	Queue* CreateQueue()
	{
		Queue* object = (Queue*)calloc(1, sizeof(Queue));
		// If allocation was successcfull...
		if (object)
		{
			object->head = object->tail = object->next = NULL;

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

		while (runner != NULL)
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

		// If the object is empty, prepare the first element
		if (!(object->head))
		{
		object->key = element;
		object->head = object->tail = object;
		}
		else
		{
			// If object contains something, regular add
			object->tail->next = _new;
			object->tail = _new;
			object->tail->key = element;
			_new->head = object;
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
		Queue* q = object;
		object->head = object->head->next;

		return x;



	}


	// Return true if the queue is empty
	int qEmpty(Queue * list)
	{
		return !list->head;
	}


	//Clear the queue
	void qClear(Queue * list)
	{
		while (!qEmpty(list))
		{
			Dequeue(list);
		}
		list->head = list->tail = list->next = NULL;
	}


	//Delete the queue from memory
	void qRemove(Queue ** list)
	{
		qClear(*list);
		free(*list);
		*list = NULL;
	}
}
