#include "tableFIFO.h"


namespace table
{
	// Default constructor
	Queue* CreateQueue(int size)
	{
		Queue* queue = (Queue*)calloc(1, sizeof(Queue));
		queue->table = (int*)calloc(size, sizeof(int));
		
		// If allocation was succesfull continue, if not return null
		if (queue && queue->table)
		{
			queue->size = size;
			queue->first = queue->table;
			queue->last = queue->table;
			queue->isFull = false;

			return queue;
		}
		return NULL;
	}

	// Check if there are any elements in the queue
	int qEmpty(Queue* queue)
	{
		return (queue->first == queue->last && !queue->isFull);
	}

	// Insert an element into the queue
	void Enqueue(Queue* queue, int element)
	{
		// First check if the queue is not full
		if (queue->isFull)
		{
			printf("ERROR<Enqueue()>: Queue overflow\n");
			return;
		}

		// Insert an element
		*queue->last = element;
		MoveLastPointer(&queue);

		// Check if the queue is full now
		if (queue->first == queue->last)
			queue->isFull = true;
	}

	// Remove the first element from the queue
	int Dequeue(Queue* queue)
	{
		// Check if we have anything to do
		if (qEmpty(queue))
		{
			printf("ERROR<Dequeue()>: Queue underflow\n");
			return 0;
		}

		// Remove the element
		int x = *queue->first;
		MoveFirstPointer(&queue);

		// Now the queue isn't full so...
		queue->isFull = false;

		return x;
	}

	// Print the queue one element in line
	void ShowQueue(Queue* queue)
	{
		// Remember original position of the first pointer due to usage of 'MoveFirstPointer()' function
		int* pointer = queue->first;

		// If there is anything to do...
		if (!qEmpty(queue))
			do
			{
				printf("%d\n", *queue->first);

				// We have a ready function, it mooves the first pointer, so... 
				// IMPORTANT: first remember original position of the first pointer
				MoveFirstPointer(&queue);

			} while (queue->first != queue->last);

			// Restore the first pointer
			queue->first = pointer;
	}

	// Reset the queue
	void qClear(Queue* queue)
	{
		queue->first = queue->last = queue->table;
	}

	// Erase the queue from the memory
	void qRemove(Queue** queue)
	{
		free((*queue)->table);
		free(*queue);
		*queue = NULL;
	}

#pragma region Helpers

	// Helper functions for moving pointers
	// This could be done by a separate class 'IteratorQ'


	void MoveFirstPointer(Queue** t)
	{
		if ((*t)->first == (*t)->table + (*t)->size - 1)
			// Moving first pointer to the beginning
			(*t)->first = (*t)->table;
		else
			//Casually moving first pointer
			(*t)->first++;
	}

	void MoveLastPointer(Queue** t)
	{
		if ((*t)->last == (*t)->table + (*t)->size - 1)
			// Moving last pointer to the beginning
			(*t)->last = (*t)->table;
		else
			//Casually moving last pointer
			(*t)->last++;
	}


#pragma endregion

}