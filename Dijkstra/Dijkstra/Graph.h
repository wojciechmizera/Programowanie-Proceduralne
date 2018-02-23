#pragma once
#include <stdio.h>
#include <memory>
#include "PQueue.h"

typedef struct tagList 
{
	int target;
	double length;
	double time;
	tagList *next;
} List;

typedef struct tagVertex 
{
	List *list;
	int nearestShop;
	int type;
	double wayToShop;
	int *path;
	double time;
} Vertex;

void DFS(Vertex *village, int speed, int *tab, int nr);
double Dijkstra(Vertex *village, int size, int first);
void PrintGraph(Vertex *village, int size);
void ReadData(FILE *file, Vertex *vertex);
Vertex* CreateVertex(int size);
void DeleteVertex(Vertex **village, int size);