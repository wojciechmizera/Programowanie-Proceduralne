// PriorityQueue.cpp : Defines the entry point for the console application.
//


#include <stdio.h>
#include "PQueue.h"

int main()
{
	PQueue* q = QCreate(20);

	for (int i = 0; i < 10; i++)
	{
		QEnqueue(q, i, i);
	}

	PQPrint(q);
	printf("\nIncreasing\n");
	IncreasePrior(q, 5, 7);
	PQPrint(q);

	for (int i = 0; i < 6; i++)
	{
		printf("%d\n", QDequeue(q));
	}

	PQPrint(q);

	DecreasePrior(q, 1, 0);

	printf("Decreasing\n");
	PQPrint(q);

	while (!QEmpty(q))
		printf("%d\n", QDequeue(q));

	QRelease(&q);

	printf("After release pointer is on: %d\n\n", (int)q);
	

    return 0;
}

