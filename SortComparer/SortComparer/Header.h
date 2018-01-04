#pragma once

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <memory>


void ShowTable(int* table, int size);
void CreateTable(int size, int** table);
void CopyTable(int* pattern, int** destination, int size);
void Timer(void(*function[])(int* table, int size), int fSize, int* table, int tSize, char* names[]);

void HalfSort(int* table, int size);		// ok

void InsertionSort(int* table, int size);	// ok

void SelectionSort(int* table, int size);	// ok

void ShakeSort(int* table, int size);		// ok

void QSort(int* table,int left, int right);	// ok

void MrgSort(int* table, int start, int koniec);
void Merge(int* table, int start, int srodek, int koniec);

void MergeSortIter(int* table, int size);	// ok

void HeapSort(int* table, int size);		// ok
void Sift(int* table, int size, int l);
void Heapify(int* table, int size);


#pragma region Miscellaneous

// Additional function specifically for recursive sorting algorithms
void TimerRecursive(void(*function[])(int* table, int left, int right), int fSize, int* table, int tSize, char* names[]);

// Mergesort using two tables, less effective
void mergeSort(int* table, int left, int right);
void merge(int* table, int left, int middle, int right);

#pragma endregion
