#include "tableFIFO.h"


namespace table
{
	// Default constructor
	Queue* CreateQueue(int size)
	{
		Queue* queue = (Queue*)calloc(1, sizeof(Queue));

		if (!queue)
		{
			printf("Error<CreateQueue()>: Memory for object not allocated\n");
			return NULL;
		}
		queue->table = (int*)calloc(size, sizeof(int));

		if (!(queue->table))
		{
			printf("ERROR<CreateQueue()>: Memory for table not allocated\n");
			return NULL;
		}

		queue->maxSize = size;
		queue->first = queue->last = queue->size = 0;

		return queue;
	}

	// Check if there are any elements in the queue
	int QEmpty(Queue* queue)
	{
		return !(queue->size);
	}


	// Insert an element into the queue
	void QEnqueue(Queue* queue, int element)
	{
		if (queue->size == queue->maxSize)
		{
			printf("ERROR<Enqueue()>: Queue overflow\n");
			return;
		}

		// Insert an element
		queue->table[queue->last] = element;
		queue->last = (queue->last+1) % queue->maxSize;
		queue->size++;
	}

	// Remove the first element from the queue
	int QDequeue(Queue* queue)
	{
		if (QEmpty(queue))
		{
			printf("ERROR<Dequeue()>: Queue underflow\n");
			return 0;
		}

		// Remove the element
		int x = queue->table[queue->first];
		queue->first = (queue->first+1) % queue->maxSize;
		queue->size--;

		return x;
	}

	// Print the queue one element in line
	void ShowQueue(Queue* queue)
	{
		for (int i = 0; i < queue->size; i++)
		{
			printf("%d\n", queue->table[(queue->first + i) % queue->maxSize]);
		}
	}

	// Reset the queue
	void QClear(Queue* queue)
	{
		queue->first = queue->last = queue->size = 0;
	}

	// Erase the queue from the memory
	void QRemove(Queue** queue)
	{
		free((*queue)->table);
		free(*queue);
		*queue = NULL;
	}
}