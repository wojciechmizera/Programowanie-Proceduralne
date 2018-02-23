#include "tableFIFO.h"


	// Default constructor
	Queue* CreateQueue(int size)
	{
		Queue* queue = (Queue*)calloc(1, sizeof(Queue));
		queue->table = (int*)calloc(size, sizeof(int));
		
		// If allocation was succesfull continue, if not return null
		if (queue && queue->table)
		{
			queue->size = size;
			queue->last = queue->table;
			queue->isFull = false;

			return queue;
		}
		return NULL;
	}


	// Check if there are any elements in the queue
	int qEmpty(Queue* queue)
	{
		return (queue->table == queue->last);
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

		queue->last++;

		// Check if the queue is full now
		if (queue->table + queue->size == queue->last)
			queue->isFull = true;

		// Update the heap if necessary, possibly a separate function
		{
			// Get the actual size of the queue in ptrdiff_t
			int right = queue->last - queue->table;

			Heapify(queue->table, right);

			while (right > 1)
			{
				// Swap the Zero and Right element
				int swap = *(queue->table);
				*(queue->table) = queue->table[--right];
				queue->table[right] = swap;

				Sift(queue->table, right, 0);
			}
		}


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
		int x = *queue->table;

		
		// Update the table, so elements' indexes always start with 0
		int i = 0;
		while (i < queue->size)
		{
			// We need both i and i+1 in one line yet we still need to increment i
			queue->table[i++] = queue->table[i+1];
		}
		queue->last--;

		// Now the queue isn't full so...
		queue->isFull = false;

		return x;
	}


	// Print the queue one element in line
	void ShowQueue(Queue* queue)
	{
		// Remember original position of the first pointer
		int* pointer = queue->table;

		// If there is anything to do...
		if (!qEmpty(queue))
			do
			{
				printf("%d\n", *pointer++);
			} while (pointer != queue->last);

	}

	// Reset the queue
	void qClear(Queue* queue)
	{
		// Can also set the memory to zeros
		queue->last = queue->table;
	}

	// Erase the queue from the memory
	void qRemove(Queue** queue)
	{
		free((*queue)->table);
		free(*queue);
		*queue = NULL;
	}

#pragma region Helpers



	// Update the FIFO with priorities
	void HeapSort(int* table, int size)
	{
		int right = size;
		Heapify(table, size);

		while (right > 1)
		{
			// Swap the Zero and Right element
			int swap = *table;
			*table = table[--right];
			table[right] = swap;

			Sift(table, right, 0);
		}
	}


	void Sift(int* table, int size, int l)
	{
		int j = 2 * l + 1;
		int x = table[l];
		while (j < size)
		{
			if (j < size - 1)
				if (table[j] < table[j + 1])
					++j;
			if (x >= table[j])
				break;
			table[l] = table[j];
			l = j;
			j = 2 * l + 1; // sift
		}
		table[l] = x;
	}

	void Heapify(int* table, int size)
	{
		int l = size / 2;
		while (l)
			Sift(table, size, --l);
	}





#pragma endregion

