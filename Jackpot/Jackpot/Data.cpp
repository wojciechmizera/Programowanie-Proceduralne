#include "Data.h"


// Private interface
int LeapYear(int rok);
Day WeekDay(int dzien, int miesiac, int rok);
int SetSex(LottoPlayer* p, char c);
int SetDate(LottoPlayer* p, int d, int m, int y);
int AllocAddMem(LottoPlayer*** pTab, int nCurrSize);
int BetsAddMemory(BetType** bets, int currSize);


// Add memory for storing players, return by how much the size was increased
int AllocAddMem(LottoPlayer*** pTab, int currentSize)
{
	LottoPlayer** table = (LottoPlayer**)realloc(*pTab, (currentSize + REALLOCPLAYERS) * sizeof(*table));

	if (!table) //komunikat o bkedzie!!!!!!!!!!!!!
	{
		printf("ERROR<AllocAddMem()>: Failed to realloc table\n");
		return 0;
	}
	memset(table + currentSize, 0, REALLOCPLAYERS * sizeof(*table));

	*pTab = table;
	table = NULL;

	return REALLOCPLAYERS;
}

// Add memory for storing bets, return by how much the size was increased
int BetsAddMemory(BetType** bets, int currentSize)
{
	BetType* table = (BetType*)realloc(*bets, (currentSize + REALLOCBETS) * sizeof(BetType));


	if (!table) //komunikat o bkedzie!!!!!!!!!
	{
		printf("ERROR<AllocAddMem()>: Failed to realloc table\n");
		return 0;
	}

	memset(table + currentSize, 0, REALLOCBETS * sizeof(*table));

	*bets = table;
	table = NULL;

	return REALLOCBETS;
}


// Read file specified by 'sFileName' and write data into pAllDraws
int ReadData(LottoPlayer*** pAllDraws, const char* sFileName)
{
	FILE* fin = NULL;

	if (!(fin = fopen(sFileName, "r")))
	{
		printf("ERROR<ReadData()>: Failed to open specified file\n");
		return 0;
	}

	int dataRead = 0;
	int maxSize = 0;

	LottoPlayer** table = *pAllDraws;

	while (!feof(fin))
	{
		// Create space for pointers
		if (dataRead == maxSize)
		{
			maxSize += AllocAddMem(&table, dataRead);
			if (dataRead == maxSize)
				break;
		}

		LottoPlayer* player = table[dataRead] = (LottoPlayer*)calloc(1, sizeof(LottoPlayer));

		int day;
		int month;
		int year;
		char sex;

		// For shortening expression
		SwiftType* swift = &player->account.swift;
		IbanType* iban = &player->account.iban;

		fscanf(fin, "* %s %s %c %8c %3c %2c %2c %8c %16c %d/%d/%d %10c",
			player->surname, player->name, &sex, swift->bankID, swift->control,
			iban->countryID, iban->control, iban->bankID, iban->personal_ID,
			&day, &month, &year, player->peselNumber);

		if (!SetSex(player, sex))
		{
			printf("ERROR<ReadData()>: Failed to set sex\n");//!!!!!!!spr
			break;
		}

		if (!SetDate(player, day, month, year))
		{
			printf("ERROR<ReadData()>: Failed to set date\n");//!!!!!!!spr
			break;
		}

		int firstNumber;
		while (fscanf(fin, "%d", &firstNumber) && !feof(fin))
		{
			// Add memory if needed
			if (player->currentSize == player->maxSize)
			{
				player->maxSize += BetsAddMemory(&player->betTable, player->currentSize);
				//!!!!
				if (player->currentSize == player->maxSize)
					break;
			}

			// Prepare tables using helper pointer
			BetType* bets = player->betTable;
			int* v1 = bets[player->currentSize].numbers = (int*)calloc(N, sizeof(int));
			int* v2 = bets[player->currentSize].euroNumbers = (int*)calloc(EN, sizeof(int));

			// Read and write numbers into tables
			*v1++ = firstNumber;
			for (int i = 1; i < N; i++)
				fscanf(fin, "%d", v1++);

			fscanf(fin, "%d %d", v2, v2 + 1);

			player->currentSize++;
		}
		dataRead++;
	}

	HeapCheck();

	*pAllDraws = table;

	fclose(fin);
	return dataRead;
}



// Set gender for a player
int SetSex(LottoPlayer* p, char c)
{
	switch (tolower(c))
	{
	case 'f':
		p->gender = female;
		return 1;
	case 'm':
		p->gender = male;
		return 1;
	default:
		return 0;
	}
}


// Set a date for the player
int SetDate(LottoPlayer* p, int d, int m, int y)
{
	// Check the initial conditions 
	if (d < 1 || d>31 || m < 1 || m>12 || y < 1900)
		return NULL;

	p->date.day = d;
	p->date.year = y;
	p->date.month = (Month)m;
	p->date.day_of_week = WeekDay(d, m, y);

	return 1;
}


// Indicates wheather the specified year is a leap year or not
int LeapYear(int rok) { return ((rok % 4 == 0 && rok % 100 != 0) || rok % 400 == 0); }


// Returns day of the week for specified date
Day WeekDay(int day, int month, int year)
{
	// Number of days from the beginning of the year(common)
	int nrOfDays[] = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 };

	int dayOfYear;
	int yy, c, g;
	int result;

	dayOfYear = day + nrOfDays[month - 1];
	if ((month > 2) && (LeapYear(year)))
		dayOfYear++;

	yy = (year - 1) % 100;
	c = (year - 1) - yy;
	g = yy + (yy / 4);
	result = ((((c / 100) % 4) * 5) + g) % 7;
	result += dayOfYear - 1;
	result %= 7;

	return (Day)result;
}


// Calculate statistics for Numbers
void CalcStat50(int* pNums, LottoPlayer** pDraws, int nDrawsNo)
{
	// For all players
	for (int i = 0; i < nDrawsNo; i++)
	{
		// For every bet made by player
		for (int j = 0; j < pDraws[i]->currentSize; j++)
		{
			// Check each number
			for (int k = 0; k < N; k++)
			{
				pNums[pDraws[i]->betTable[j].numbers[k] - 1]++;
			}
		}
	}
}


// Same as above, EuroNumbers
void CalcStat10(int* pNums, LottoPlayer** pDraws, int nDrawsNo)
{
	for (int i = 0; i < nDrawsNo; i++)
		for (int j = 0; j < pDraws[i]->currentSize; j++)
			for (int k = 0; k < EN; k++)
				pNums[pDraws[i]->betTable[j].euroNumbers[k] - 1]++;
}




// Delete players from table
void FreeMem(LottoPlayer** pTab, int nDrawsNo)
{
	for (int i = 0; i < nDrawsNo; i++)
	{
		for (int j = 0; j < pTab[i]->maxSize; j++)
		{
			// Free dynamically allocated memory
			free(pTab[i]->betTable[j].numbers);
			pTab[i]->betTable[j].numbers = NULL;
			free(pTab[i]->betTable[j].euroNumbers);
			pTab[i]->betTable[j].euroNumbers = NULL;
		}
		// Delete player
		free(pTab[i]);
		pTab[i] = NULL;
	}
}

// Check the status of the heap after reallocating memory
void HeapCheck()
{
	int heapstatus = _heapchk();
	switch (heapstatus)
	{
	case _HEAPOK:
		printf("OK  _HEAPOK\n");
		break;
	case _HEAPEMPTY:
		printf("OK  _HEAPEMPTY\n");
		break;
	case _HEAPBADBEGIN:
		printf("ERROR _HEAPBADBEGIN\n");
		break;
	case _HEAPBADNODE:
		printf("ERROR _HEAPBADNODE\n");
		break;
	}
}
