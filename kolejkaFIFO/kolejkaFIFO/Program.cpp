// kolejkaFIFO.cpp : Defines the entry point for the console application.
//



#include "tableFIFO.h"
#include "listFIFO.h"
#include "nullList.h"


#include <iostream>
using namespace std;

void TableTester();
void ListTester();
void NullTester();


	using namespace NullList;

int main()
{
	TableTester();
	ListTester();
	NullTester();

	return 0;
}



void NullTester()
{
	NullList::Queue* fifo =  NullList::CreateQueue();

	printf("Queue is empty: %d\n", NullList::qEmpty(fifo));

	printf("Enqueueing 10 elements:\n");
	for (int i = 0; i < 10; i++)
	{
		NullList::Enqueue(fifo, i + 1);
	}

	printf("Printing queue:\n");
	NullList::ShowQueue(fifo);

	printf("Dequeueing 6 elements:\n");
	for (int i = 0; i < 6; i++)
	{
		printf("%d,  ", NullList::Dequeue(fifo));
	}
	printf("\n");

	printf("Printing queue:\n");
	NullList::ShowQueue(fifo);

	printf("Enqueueing 4 new elements:\n");
	for (int i = 14; i < 18; i++)
	{
		NullList::Enqueue(fifo, i);
	}

	printf("Printing queue:\n");
	NullList::ShowQueue(fifo);

	printf("Queue is empty: %d\n", NullList::qEmpty(fifo));

	printf("Clearing queue\n");
	NullList::qClear(fifo);


	printf("Queue is empty: %d\n", NullList::qEmpty(fifo));

	printf("Printing queue:\n");
	NullList::ShowQueue(fifo);

	printf("Removing queue\n");
	NullList::qRemove(&fifo);

	printf("Now pointer is on: %d\n", (int)fifo);
}



void ListTester()
{
	list::Queue* fifo = list::CreateQueue();

	printf("Queue is empty: %d\n", list::qEmpty(fifo));

	printf("Enqueueing 10 elements:\n");
	for (int i = 0; i < 10; i++)
	{
		list::Enqueue(fifo, i + 1);
	}

	printf("Printing queue:\n");
	list::ShowQueue(fifo);

	printf("Dequeueing 6 elements:\n");
	for (int i = 0; i < 6; i++)
	{
		printf("%d,  ", list::Dequeue(fifo));
	}
	printf("\n");

	printf("Printing queue:\n");
	list::ShowQueue(fifo);

	printf("Enqueueing 4 new elements:\n");
	for (int i = 14; i < 18; i++)
	{
		list::Enqueue(fifo, i);
	}

	printf("Printing queue:\n");
	list::ShowQueue(fifo);

	printf("Queue is empty: %d\n", list::qEmpty(fifo));

	printf("Clearing queue\n");
	list::qClear(fifo);


	printf("Queue is empty: %d\n", list::qEmpty(fifo));

	printf("Printing queue:\n");
	list::ShowQueue(fifo);

	printf("Removing queue\n");
	list::qRemove(&fifo);

	printf("Now pointer is on: %d\n", (int)fifo);
}


void TableTester()
{
	table::Queue* fifo = table::CreateQueue(12);

	printf("Creating new queue, size of table: %d\n", fifo->maxSize);

	printf("Queue is empty: %d\n", table::QEmpty(fifo));

	printf("Enqueueing 10 elements:\n");
	for (int i = 0; i < 10; i++)
	{
		table::QEnqueue(fifo, i + 1);
	}

	printf("Printing queue:\n");
	table::ShowQueue(fifo);

	printf("Dequeueing 6 elements:\n");
	for (int i = 0; i < 6; i++)
	{
		printf("%d,  ", table::QDequeue(fifo));
	}
	printf("\n");

	printf("Printing queue:\n");
	table::ShowQueue(fifo);

	printf("Enqueueing 4 new elements:\n");
	for (int i = 14; i < 18; i++)
	{
		table::QEnqueue(fifo, i);
	}

	printf("Printing queue:\n");
	table::ShowQueue(fifo);

	printf("Queue is empty: %d\n", table::QEmpty(fifo));

	printf("Clearing queue\n");
	table::QClear(fifo);


	printf("Queue is empty: %d\n", table::QEmpty(fifo));

	printf("Printing queue:\n");
	table::ShowQueue(fifo);

	printf("Removing queue\n");
	table::QRemove(&fifo);

	printf("Now pointer is on: %d\n", (int)fifo);
}
