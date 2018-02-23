#include "Print.h"

// Private interface
void PrintSex(FILE* fout, LottoPlayer* p);                        
void PrintDate(FILE* fout, LottoPlayer* p);                       
void PrintBets(FILE* fout, LottoPlayer* p);						  
void PrintStats(FILE* fout, int* stats50, int* stats10);		  




void PrintSex(FILE* fout, LottoPlayer* p)
{
	char* sex = NULL;
	switch (p->gender)
	{
	case male: sex = "*Facet*"; break;
	case female: sex = "*Panienka*"; break;
	}
	fprintf(fout, "%-15s", sex);
}


void PrintDate(FILE* fout, LottoPlayer* p)
{
	switch (p->date.day_of_week)
	{
	case Mon: fprintf(fout, "Mon, "); break;
	case Tue: fprintf(fout, "Tue, "); break;
	case Wed: fprintf(fout, "Wed, "); break;
	case Thu: fprintf(fout, "Thu, "); break;
	case Fri: fprintf(fout, "Fri, "); break;
	case Sat: fprintf(fout, "Sat, "); break;
	case Sun: fprintf(fout, "Sun, "); break;
	}

	fprintf(fout, "%3d/", p->date.day);

	switch (p->date.month)
	{
	case Jan: fprintf(fout, "Jan/"); break;
	case Feb: fprintf(fout, "Feb/"); break;
	case Mar: fprintf(fout, "Mar/"); break;
	case Apr: fprintf(fout, "Apr/"); break;
	case May: fprintf(fout, "May/"); break;
	case Jun: fprintf(fout, "Jun/"); break;
	case Jul: fprintf(fout, "Jul/"); break;
	case Aug: fprintf(fout, "Aug/"); break;
	case Sep: fprintf(fout, "Sep/"); break;
	case Oct: fprintf(fout, "Oct/"); break;
	case Nov: fprintf(fout, "Nov/"); break;
	case Dec: fprintf(fout, "Dec/"); break;
	}

	fprintf(fout, "%-10d", p->date.year);
}


void PrintBets(FILE* fout, LottoPlayer* p)
{
	BetType* bets = p->betTable;

	for (int i = 0; i < p->currentSize; i++)
	{
		for (int j = 0; j < N; j++)
			fprintf(fout, "%2d  ", bets[i].numbers[j]);
		
		fprintf(fout, "\t");

		for (int j = 0; j < EN; j++)
			fprintf(fout, "%2d  ", bets[i].euroNumbers[j]);

		fprintf(fout, "\n");
	}
}


void PrintStats(FILE* fout, int* stats50, int* stats10)
{
	fprintf(fout, "===================================================\n"
				  "               S T A T I S T I C S\n"
				  "===================================================\n");

	for (int i = 0; i < STATN; i++)
	{
		fprintf(fout, "%2d:%2d\t", i + 1, stats50[i]);
		if (!((i + 1) % 10)) fprintf(fout, "\n");
	}
	fprintf(fout, "\n");
	for (int i = 0; i < STATEN; i++)
	{
		fprintf(fout, "%2d:%2d\t", i + 1, stats10[i]);
		if (!((i + 1) % 10)) fprintf(fout, "\n");
	}

}



void PrintResults(LottoPlayer** pDraws, int nDrawsNo, int* stats50, int* stats10)
{
	FILE* fin = NULL;

	if ((fin = fopen("wyniki.txt", "w")) == NULL)
	{
		printf("EROOR<PrintResults()>: Could not open file 'wyniki.txt.\n");
		return;
	}
	char* names = (char*)calloc(2, MAX);

	for (int i = 0; i < nDrawsNo; i++)
	{
		LottoPlayer* player = pDraws[i];
		strcpy(names, pDraws[i]->name);
		strcat(names, " ");
		strcat(names, pDraws[i]->surname);

		fprintf(fin, " %-30s", names);
		PrintSex(fin, pDraws[i]);
		PrintDate(fin, pDraws[i]);
		SwiftType* swift = &pDraws[i]->account.swift;
		IbanType* iban = &pDraws[i]->account.iban;
		fprintf(fin, "  %s%s   %s%s%s%s  %s\n", swift->bankID, swift->control, iban->countryID, iban->control, iban->bankID, iban->personal_ID, pDraws[i]->peselNumber);

		for (int i = 0; i < 5; i++)
			fprintf(fin, "=========================");
		fprintf(fin, "\n");

		PrintBets(fin, pDraws[i]);

		fprintf(fin, "\n");
	}

	PrintStats(fin, stats50, stats10);

	fclose(fin);
	free(names);
}
