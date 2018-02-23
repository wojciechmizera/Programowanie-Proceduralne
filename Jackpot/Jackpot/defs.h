#pragma once

#include <stdio.h>
#include <ctype.h>
#include <memory>


#define STATN 50		// 5 / 50
#define N 5				// 5 / 50
#define STATEN 10		// 2 / 10
#define EN 2			// 2 / 10

#define MAX 20			// Max length of name / surname
#define PESELNR 11		// Pesel nr

#define REALLOCPLAYERS 5		// Increase step of nr of players
#define REALLOCBETS 3			// Increase step of nr of bets for a player

#define SWIFTTYPE 9		// i.e. ~ALBPPLPW~XXX
#define SWIFTCONTROL 4	// i.e. ALBPPLPW~XXX~

#define IBANCTRL 3		//  CountryID and control nr i.e. ~PL~ ~61~ 12345678 0002200022346678
#define IBANP 17		// PL 61 12345678 ~0002200022346678~
#define IBANB 9			// PL 61 ~12345678~ 0002200022346678

typedef enum
{
	Mon,
	Tue,
	Wed,
	Thu,
	Fri,
	Sat,
	Sun
}Day;

typedef	enum
{
	male,
	female
}SexType;

typedef enum
{
	// bez przywiazywania do wartosci, zmienic w setdate
	Jan,
	Feb,
	Mar,
	Apr,
	May,
	Jun,
	Jul,
	Aug,
	Sep,
	Oct,
	Nov,
	Dec
}Month;

typedef struct tagDate
{
	Day day_of_week;
	Month month;
	int year;
	int day;
}DateType;

typedef struct tagIbanType
{
	char personal_ID[IBANP];
	char countryID[IBANCTRL];
	char bankID[IBANB];
	char control[IBANCTRL];
}IbanType;

typedef struct tagSwiftCode
{
	char bankID[SWIFTTYPE];
	char control[SWIFTCONTROL];
}SwiftType;

typedef struct tagAccount
{
	SwiftType swift;
	IbanType iban;
}AccountType;

typedef struct tagBetType
{
	int* numbers;
	int* euroNumbers;
}BetType;

typedef struct tagLottoPlayer
{
	char name[MAX+1];
	char surname[MAX+1];
	char peselNumber[PESELNR];
	int maxSize;
	int currentSize;
	AccountType account;
	BetType* betTable;
	DateType date;
	SexType gender;
}LottoPlayer;
