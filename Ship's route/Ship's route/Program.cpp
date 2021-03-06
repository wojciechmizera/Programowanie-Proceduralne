// Ship's route.cpp : Defines the entry point for the console application.
//

#include "Ship.h"


int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		printf("Usage: %s <datafile>\n", argv[0]);
		return 1;
	}

	int** depthMap = NULL;
	int** rootMap = NULL;

	CreateMap(&depthMap, N, M);
	CreateMap(&rootMap, N, M);

	if (depthMap == 0 || rootMap == 0)
	{
		printf("Error<main()>: Creation of maps unsuccessful\n");
		return 1;
	}

	setTab(argv[1], depthMap, N, M);
	
	PrintMap(depthMap, N, M);

	printf("\n\n");
	
	int result = root(depthMap, N, M, DEPTH_MIN, 0, 0, rootMap, N - 1, M - 1);
	
	if (result)
		PrintMap(rootMap, N, M);
	else
		printf("The way doesn't exist\n");

	DeleteMap(&depthMap, N);
	DeleteMap(&rootMap, N);

    return 0;
}

