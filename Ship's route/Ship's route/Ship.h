#pragma once

#include <stdio.h>
#include <memory>

enum Directions
{
	UP,
	RIGHT,
	DOWN,
	LEFT
};

#define DEPTH_MIN 10
#define N 10
#define M 10

// Allocate memory
int CreateMap(int*** matrix, int rows, int cols);

// Function printing matrix
void PrintMap(int** map, int rows, int cols);


void setTab(char* sFile, int** pTab, int nRow, int nCol);

// Free memory allocated for a matrix
void DeleteMap(int*** table, int rows);


/* pTab - tablica okreslajaca glebokosc w kazdym kwadracie
nRow, nCol - rozmia pTab,
nDepth - minimalna glebokosc aby statek przpelynal
x, y - indeksy w tablicy skad wykonujemy kolejny ruch np. zaczynamy od 0,0
move_nr - kierunek ruchu
ps py - nowe wspolrzedne
pRoot - tablica pamietajaca ruchy o rozm nRow, nCol
*/
int move(int** pTab, int nRow, int nCol, int nDepth, int move_nr, int x, int y, int* px, int* py, int** pRoot);



/* pTab tabl glebokosci   o romiarze bRow  i nCol
dDepth - glebokosc zanurzenia ststku
x, y - wspol skad robimy kolejny ruch
pRoot tablica kolejnych ruchow
x_dest, y_dest - wsporzedne portu
*/
int root(int** pTab, int nRow, int nCol, int nDepth, int x, int y, int** pRoot, int x_dest, int y_dest);

