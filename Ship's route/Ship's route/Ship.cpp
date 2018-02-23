#include "Ship.h"



// Create map
int CreateMap(int*** map, int rows, int cols)
{
	*map = (int**)calloc(rows, sizeof(int*));

	int** temp = *map;
	for (int i = 0; i < rows; i++)
		*temp++ = (int*)calloc(cols, sizeof(int));

	// If something went wrong return false
	if (map == NULL)
		return 0;

	return 1;
}


// Read the file
void ReadMap(int rows, int cols, int ** map, FILE * file)
{
	for (int i = 0; i < rows; i++)
	{
		// Auxiliary pointer
		int* v = *map++;

		for (int j = 0; j < cols; j++, v++)
			fscanf(file, "%d", v);
	}
}


// Function printing map
void PrintMap(int** map, int rows, int cols)
{
	for (int i = 0; i < rows; i++)
	{
		int* v = *map++;
		for (int j = 0; j < rows; j++, v++)
			printf("%d\t", *v);

		printf("\n");
	}
}


void setTab(char* sFile, int** pTab, int nRow, int nCol)
{
	FILE* file;

	if ((file = fopen(sFile, "r")) == NULL)
	{
		printf("ERROR: no such file\n");
		// Function void, but the return value would solve the problem with completing main() with invalid data
		return;
	}

	for (int i = 0; i < nRow; i++)
	{
		// Auxiliary pointer
		int* v = *pTab++;

		for (int j = 0; j < nCol; j++, v++)
			fscanf(file, "%d", v);
	}
}


// Free memory allocated for a map
void DeleteMap(int*** table, int rows)
{
	int** tab = *table;
	for (int i = 0; i < rows; i++)
		free(*(tab + i));

	free(*table);
	*table = NULL;
}


/* pTab - tablica okreslajaca glebokosc w kazdym kwadracie
nRow, nCol - rozmia pTab,
nDepth - minimalna glebokosc aby statek przpelynal
x, y - indeksy w tablicy skad wykonujemy kolejny ruch np. zaczynamy od 0,0
move_nr - kierunek ruchu
px py - nowe wspolrzedne
pRoot - tablica pamietajaca ruchy o rozm nRow, nCol
*/
int move(int** pTab, int nRow, int nCol, int nDepth, int move_nr, int x, int y, int* px, int* py, int** pRoot)
{
	switch (move_nr)
	{
	case 0: y--; break;
	case 1: x++; break;
	case 2: y++; break;
	case 3: x--; break;
	}

	// Check frame
	if (x < 0 || x >= nCol || y < 0 || y >= nRow) return 0;
	// Check depth
	if (pTab[y][x] < nDepth) return 0;
	// Check if visited
	if (pRoot[y][x]) return 0;

	// Set new position if everything is OK
	*px = x;
	*py = y;

	return 1;
}


/* pTab tabl glebokosci   o romiarze bRow  i nCol
dDepth - glebokosc zanurzenia ststku
x, y - wspol skad robimy kolejny ruch
pRoot tablica kolejnych ruchow
x_dest, y_dest - wsporzedne portu
*/
int root(int** pTab, int nRow, int nCol, int nDepth, int x, int y, int** pRoot, int x_dest, int y_dest)
{
	pRoot[y][x] = 1;

	if (x == x_dest && y == y_dest)
		return 1;

	int newX;
	int newY;

	for (int d = UP; d <= LEFT; d += 1)
		if (move(pTab, N, M, DEPTH_MIN, d, x, y, &newX, &newY, pRoot))
			if (root(pTab, N, M, DEPTH_MIN, newX, newY, pRoot, x_dest, y_dest))
				return 1;

	pRoot[y][x] = 0;

	return 0;
}
