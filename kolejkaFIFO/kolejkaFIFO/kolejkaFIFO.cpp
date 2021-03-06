// kolejkaFIFO.cpp : Defines the entry point for the console application.
//

// TODO using namespaces to separate modules
// TODO second version of list queue


#include "tableFIFO.h"
#include "listFIFO.h"
#include "nullList.h"


#include <iostream>
using namespace std;

void TableTester();
void ListTester();

	using namespace NullList;

int main()
{

#pragma region Program
	//TableTester();
	//ListTester();
#pragma endregion


	Queue* q = CreateQueue();

	cout << "qempty: " << qEmpty(q) << endl;

	for (int i = 0; i < 10; i++)
	{
		Enqueue(q, i);
	}
	cout << "qempty: " << qEmpty(q) << endl;

	ShowQueue(q);
	cout << "after showing" << endl;

	cout << "dequeued: " << Dequeue(q) << endl;

	cout << "Showing after dequeue" << endl;
	ShowQueue(q);

	cout << endl;
	Enqueue(q, 89);
	ShowQueue(q);

	qClear(q);

	cout << "after clear:" << endl;
	ShowQueue(q);

	cout << "showed empty" << endl;

	Enqueue(q, 7);
	ShowQueue(q);

	qRemove(&q);
	cout << "Now pointer on: " << q << endl;



	return 0;
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

	printf("Creating new queue, size of table: %d\n", fifo->size);

	printf("Queue is empty: %d\n", table::qEmpty(fifo));

	printf("Enqueueing 10 elements:\n");
	for (int i = 0; i < 10; i++)
	{
		table::Enqueue(fifo, i + 1);
	}

	printf("Printing queue:\n");
	table::ShowQueue(fifo);

	printf("Dequeueing 6 elements:\n");
	for (int i = 0; i < 6; i++)
	{
		printf("%d,  ", table::Dequeue(fifo));
	}
	printf("\n");

	printf("Printing queue:\n");
	table::ShowQueue(fifo);

	printf("Enqueueing 4 new elements:\n");
	for (int i = 14; i < 18; i++)
	{
		table::Enqueue(fifo, i);
	}

	printf("Printing queue:\n");
	table::ShowQueue(fifo);

	printf("Queue is empty: %d\n", table::qEmpty(fifo));

	printf("Clearing queue\n");
	table::qClear(fifo);


	printf("Queue is empty: %d\n", table::qEmpty(fifo));

	printf("Printing queue:\n");
	table::ShowQueue(fifo);

	printf("Removing queue\n");
	table::qRemove(&fifo);

	printf("Now pointer is on: %d\n", (int)fifo);
}
