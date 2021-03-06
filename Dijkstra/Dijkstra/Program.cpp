// Dijkstra.cpp : Defines the entry point for the console application.
//
#include "Graph.h"
#define SPEED 5

int main(int argc, char* argv[]) 
{
	if (argc != 2) 
	{
		printf("Usage: %s <Data file> \n", argv[0]);
		return 1;
	}

	FILE *file = NULL;
	if ((file = fopen(argv[1], "r")) == NULL)
	{
		printf("ERROR: No such file \n");
		return 2;
	}

	int size = 0;
	fscanf(file, "%d", &size);
	Vertex *village = CreateVertex(size);
	ReadData(file, village);

	int* tab = (int*)calloc(size, sizeof(int));
	if (!tab) 
	{
		printf("Failed to allocate memory\n");
		return 1;
	}

	DFS(village, SPEED, tab, 1);
	free(tab);
	for (int i = 0; i < size; i++) 
	{
		// Check for houses only
		if (!village[i].type) 
			village[i].wayToShop = Dijkstra(village, size, i);
	}

	PrintGraph(village, size);
	
	
	DeleteVertex(&village, size);
	fclose(file);

	return 0;
}
