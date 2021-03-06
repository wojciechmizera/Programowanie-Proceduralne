// Jackpot.cpp : Defines the entry point for the console application.
//
#include "defs.h"
#include "Print.h"
#include "Data.h"

int CompareNames(const void* p1, const void* p2);



int main(int argc, char* argv[])
{
	if (argc!=3)
	{
		printf("Usage: %s  input.txt output.txt\n", argv[0]);
		return 1;
	}

	LottoPlayer** pDraws = NULL;
	
	// Read data
	int nDrawsNo = ReadData(&pDraws, argv[1]);

	if (nDrawsNo == 0)
	{
		printf("Specified file contains no data.\n");
		return 2;
	}

	// Calculate statistics
	int* fiveFifty = (int*)calloc(STATN, sizeof(int));
	int* twoTen = (int*)calloc(STATEN, sizeof(int));
	CalcStat50(fiveFifty, pDraws, nDrawsNo);
	CalcStat10(twoTen, pDraws, nDrawsNo);

	// Sort players
	qsort(pDraws, nDrawsNo, sizeof(LottoPlayer*), CompareNames);

	// Print results to file
	PrintResults(pDraws, nDrawsNo, fiveFifty, twoTen);

	// Clean up
	FreeMem(pDraws, nDrawsNo);
	free(pDraws);
	pDraws = NULL;
	
	//!!!zwolni pamiec z stats
	free(fiveFifty);
	free(twoTen);

	HeapCheck();
	return 0;
}


// Comparer function for sorting table of players by surname, then name
int CompareNames(const void* p1, const void* p2)
{
	// Get players from void
	LottoPlayer** player1 = (LottoPlayer**)p1;
	LottoPlayer** player2 = (LottoPlayer**)p2;


	// Get strings containing surname and name of each player 
	char* str1 = (char*)calloc(MAX * 2, sizeof(char));
	char* str2 = (char*)calloc(MAX * 2, sizeof(char));
	strcpy(str1, (*player1)->surname);
	strcat(str1, (*player1)->name);
	strcpy(str2, (*player2)->surname);
	strcat(str2, (*player2)->name);

	// Could use transform()
	int i = 0;
	while (str1[i] = tolower(str1[i])) i++;

	i = 0;
	while (str2[i] = tolower(str2[i])) i++;

	int res =strcmp(str1, str2);//zapamietac wynik, zwolnic pamiec, zwrocic wynik

	free(str1);
	free(str2);
	return res;
}
