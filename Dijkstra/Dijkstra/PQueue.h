#pragma once

#include <stdio.h>
#include <memory>


// Single element of the queue
typedef struct tagPQItem
{
	int key;
	double prior;
}PQItem;


// Table of PQItem elements
typedef struct tagPQueue
{
	PQItem* array;
	int PQSize;
	int PQCurrSize;
}PQueue;


PQueue* QCreate(int size);
int QEmpty(PQueue* queue);
void QEnqueue(PQueue* queue, int key, double prior);
int QDequeue(PQueue* queue);
void QRelease(PQueue** queue);

void IncreasePrior(PQueue* queue, int index, double prior);

void DecreasePrior(PQueue* queue, int index, double prior);

void UpdateUp(PQueue* queue, int left, int right);
void UpdateDown(PQueue* queue, int left, int right);