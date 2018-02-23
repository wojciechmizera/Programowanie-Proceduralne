#pragma once

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <memory>


// Custom type to simplify complex definition of pointer, works like a delegate
typedef void(*Delegate[])(int*, int);



void ShowTable(int* table, int size);
void CreateTable(int size, int** table);
void Timer(Delegate func, int fSize, int* table, int tSize, const char* names[]);



void HalfSort(int* table, int size);

void InsertionSort(int* table, int size);

void SelectionSort(int* table, int size);

void ShakeSort(int* table, int size);

void HeapSort(int* table, int size);

void MergeSort(int* table, int size);

void QuickSort(int* table, int size);

void MergeSortS(int* tab, int nSize);
