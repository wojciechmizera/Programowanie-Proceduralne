#include "PQueue.h"


// Create a queue of <size> elements
PQueue* QCreate(int size)
{
	PQueue* queue = (PQueue*)calloc(1, sizeof(PQueue));

	if (!queue)
	{
		printf("ERROR<Qcreate()>: Not enough memory\n");
		return 0;
	}
	queue->PQSize = size;
	queue->array = (PQItem*)calloc(size, sizeof(PQItem));

	if (!queue->array)
	{
		printf("ERROR<Qcreate()>: Not enough memory\n");
		return 0;
	}
	return queue;
}


// Return true if the queue is empty
int QEmpty(PQueue* queue)
{
	return !queue->PQCurrSize;
}


// Add element to the queue
void QEnqueue(PQueue* queue, int nKey, int nPrior)
{
	if (queue->PQCurrSize == queue->PQSize)
	{
		printf("ERROR<Enqueue()>: Queueu full\n");
	}

	// Add new element
	queue->array[queue->PQCurrSize].key = nKey;
	queue->array[queue->PQCurrSize++].prior = nPrior;

	// Fix the heap
	int i = queue->PQCurrSize -1;
	UpdateUp(queue, 0, i);
}


 //Remove element from the queue
int QDequeue(PQueue* queue)
{
	if (QEmpty(queue))
	{
		printf("ERROR<Dequeue()>: Queue empty\n");
		return 0;
	}
	// Remember value
	int x = queue->array[0].key;

	// Set last element as the first one
	queue->array[0] = queue->array[--queue->PQCurrSize];
	
	// Fix the heap
	UpdateDown(queue, 0, queue->PQCurrSize);

	return x;
}


// Free memory
void QRelease(PQueue** queue)
{
	free((*queue)->array);
	free(*queue);
	*queue = NULL;
}


// Increase the priority of element at specified index
void IncreasePrior(PQueue* queue, int index, int prior)
{
	if (queue->PQCurrSize < index - 1)
	{
		printf("ERROR<DecreasePrior()>:Index out of range\n");
		return;
	}
	if (queue->array[index].prior > prior)
	{
		printf("ERROR<DecreasePrior()>:Given priority is higher than actual\n");
		return;
	}
	queue->array[index].prior = prior;
	
	UpdateUp(queue, 0, index);
}


// Decrease the priority of element at specified index
void DecreasePrior(PQueue* queue, int index, int prior)
{
	if (queue->PQCurrSize < index - 1)
	{
		printf("ERROR<DecreasePrior()>:Index out of range\n");
		return;
	}
	if (queue->array[index].prior < prior)
	{
		printf("ERROR<DecreasePrior()>:Given priority is lower than actual\n");
		return;
	}

	queue->array[index].prior = prior;

	UpdateUp(queue, 0, index);
}


void UpdateUp(PQueue* queue, int left, int right)
{
	while (right != left && queue->array[(right - 1) / 2].prior < queue->array[right].prior)
	{
		PQItem swap = queue->array[right];
		queue->array[right] = queue->array[(right - 1) / 2];
		queue->array[(right - 1) / 2] = swap;
		right = (right - 1) / 2;
	}
}


void UpdateDown(PQueue* queue, int left, int right)
{
	int j = 2 * left + 1;
	PQItem x = queue->array[left];
	while (j < right)
	{
		if (j < right - 1)
			if (queue->array[j].prior < queue->array[j + 1].prior)
				++j;
		if (x.prior >= queue->array[j].prior)
			break;
		queue->array[left] = queue->array[j];
		left = j;
		j = 2 * left + 1;
	}
	queue->array[left] = x;
}


// Print the queue
void PQPrint(PQueue* queue)
{
	for (int i = 0; i < queue->PQCurrSize; i++)
	{
		printf("%-10d%d\n", queue->array[i].key, queue->array[i].prior);
	}
}