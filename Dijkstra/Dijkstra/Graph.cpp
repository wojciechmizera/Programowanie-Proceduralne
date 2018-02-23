#include "Graph.h"

#define ADJUSTMENT 5


Vertex* CreateVertex(int size)
{
	Vertex* vertex = (Vertex*)calloc(size, sizeof(Vertex));
	if (!vertex)
	{
		printf("ERROR<CreateVertex()>: Memory for vertex not allocated\n");
		return NULL;
	}

	for (int i = 0; i < size; i++)
	{
		vertex[i].path = (int*)calloc(size, sizeof(int));
		if (!vertex[i].path)
		{
			printf("ERROR<CreateVertex()>: Memory for path not allocated\n");
			return NULL;
		}
	}
	return vertex;
}


// Read grapf from file given in args
void ReadData(FILE *file, Vertex *village)
{
	char c;
	int i = 0;
	while ((c = getc(file)) != EOF)
	{
		fscanf(file, "%d", &i);
		List* newEdge = (List*)calloc(1, sizeof(List));
		if (!newEdge)
		{
			printf("ERROR<ReadData()>: Cannot allocate memory\n");
			return;
		}

		fscanf(file, "%d %d %lf", &village[i].type, &(newEdge->target), &(newEdge->length));

		// If first run, initiate the list
		if (!(village[i].list))
		{
			village[i].list = newEdge;
		}
		// else add element to existing list
		else
		{
			List* temp = village[i].list;

			// Jump to the last position and add new object
			while (temp->next)
				temp = temp->next;
			temp->next = newEdge;
		}
	}
}


// Depth-first search
void DFS(Vertex* village, int speed, int *tab, int nr)
{
	// Set vertex as visited
	tab[nr] = 1;
	List *temp = village[nr].list;
	while (temp)
	{
		// Set time of travel for the edge
		temp->time = temp->length / speed * 60;

		// if the next target was not visited - recursion
		if (!tab[temp->target])
			DFS(village, speed, tab, temp->target);
		temp = temp->next;
	}
}

// Find the shortest way to the nearest shop
double Dijkstra(Vertex *village, int size, int first)
{
	PQueue *queue = QCreate(size);

	double *pathLength = (double*)calloc(size, sizeof(double));
	if (!pathLength)
	{
		printf("ERROR<Dijkstra()>: Memory for pathLength table not allocated\n");
		return 0;
	}

	double *time = (double*)calloc(size, sizeof(double));
	if (!time)
	{
		printf("ERROR<Dijkstra()>: Memory for time table not allocated\n");
		return 0;
	}

	for (int i = 0; i < size; i++)
	{
		// Initiate distance as inf
		pathLength[i] = INT_MAX;
		village[first].path[i] = -1;
	}

	// Add our source to the queue and set its distance as 0
	QEnqueue(queue, first, 0);
	double length = pathLength[first] = 0;

	while (!QEmpty(queue))
	{
		int element = QDequeue(queue);

		// If current element happens to be a shop break the loop
		if (village[element].type)
		{
			village[first].time = time[element];
			village[first].nearestShop = element;
			length = pathLength[element];
			QRelease(&queue);
			break;
		}

		List *tmp = village[element].list;
		while (tmp)
		{
			int nextNode = tmp->target;
			double way = tmp->length;

			// If we found shorter way update 
			if ((pathLength[element] + way) < pathLength[nextNode])
			{
				village[first].path[nextNode] = element;
				time[nextNode] = time[element] + tmp->time;
				pathLength[nextNode] = pathLength[element] + way;

				// And add next element to the queue
				QEnqueue(queue, nextNode, pathLength[nextNode]);
			}
			tmp = tmp->next;
		}
	}

	free(time);
	free(pathLength);

	return length;
}


// Write result to file
void PrintGraph(Vertex* village, int size)
{
	FILE* file = NULL;
	file = fopen("result.txt", "w");
	if (!file)
	{
		printf("ERROR<PrintGraph()>: Failed to open file for writing\n");
		return;
	}

	int* path = (int*)calloc(size, sizeof(int));
	if (!path)
	{
		printf("ERROR<PrintGraph()>: Memory for path not allocated\n");
		return;
	}

	// Cosmetics
	fprintf(file, "Path  ");
	for (int i = 0; i < ADJUSTMENT - 2; i++)
		fprintf(file, "   ");
	fprintf(file, "  Distance   Shop nr  Time\n");

	for (int i = 0; i < size; i++)
	{
		// Print way only for houses, not for shops
		if (village[i].type)
			continue;

		Vertex house = village[i];

		memcpy(path, house.path, size * sizeof(int));

		int shop = house.nearestShop;
		house.path[0] = shop;

		int j;
		for (j = 1; shop != i; j++)
		{
			house.path[j] = path[shop];
			shop = path[shop];
		}

		for (int l = j -1; l >= 0; l--)
			fprintf(file, "%2d ", house.path[l]);

		for (; j < ADJUSTMENT; j++) fprintf(file, "   ");

		fprintf(file, "  %.1lfkm      %2d       %.1lf min\n", house.wayToShop, house.nearestShop, house.time);
	}
	free(path);
	fclose(file);
}


void DeleteVertex(Vertex** vertex, int size)
{
	for (int i = 0; i < size; i++)
	{
		// First free the list
		while ((*vertex)[i].list)
		{
			List* p = (*vertex)[i].list;
			(*vertex)[i].list = (*vertex)[i].list->next;
			free(p);
		}
	}
	free(*vertex);
	vertex = NULL;
}