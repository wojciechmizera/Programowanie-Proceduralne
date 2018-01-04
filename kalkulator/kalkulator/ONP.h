#ifndef _ONP
#define _ONP


#include <stdio.h>				// jest w stosach
#include <math.h>
#include "StosLiczb.h"
#include "StosOperatorow.h"

double ONP();
int IsOper(char c);
int IsDigit(char c);
int Prior(char c);
double GetNum();
char GetOper();
void SkipSpaces();
double Calcul(char cOper, double arg1, double arg2);


double ONP()
{
	char oper;
	CharStack* listaOper = NULL;
	IntStack* listaLiczb = NULL;

	while ((oper = GetOper()) == '(')
		Push(&listaOper, oper);

	ungetc(oper, stdin);

	Push(&listaLiczb, GetNum());
	while (IsOper(oper = GetOper()))
	{
		if (oper == ')')
		{
			while ((oper = Pop(&listaOper)) != '(')
			{
				double x = Pop(&listaLiczb);
				Push(&listaLiczb, Calcul(oper, Pop(&listaLiczb), x));
			}
		}
		else
		{
			while( Prior(oper) <= Prior(Top(listaOper)) )
			{
				double x = Pop(&listaLiczb);
				Push(&listaLiczb, Calcul(Pop(&listaOper), Pop(&listaLiczb), x));
			}

			Push(&listaOper, oper);

			while ((oper = GetOper()) == '(')
				Push(&listaOper, oper);

			ungetc(oper, stdin);

			Push(&listaLiczb, GetNum());
		}
	}

	while (!IsEmpty(listaOper))
	{
		double x = Pop(&listaLiczb);
		Push(&listaLiczb, Calcul(Pop(&listaOper), Pop(&listaLiczb), x));
	}

	return Pop(&listaLiczb);
}


int IsOper(char znak)
{
	switch (znak)
	{
	case '(':
	case ')':
	case '+':
	case '-':
	case '*':
	case '/':
	case '^':
		return 1;
	}
	return 0;
}


int IsDigit(char c)
{
	return (c >= '0') && (c <= '9');
}


int Prior(char znak)
{
	switch (znak)
	{
	case '+':
	case '-': return 1;
	case '*':
	case '/': return 2;
	case '^': return 3;
	}
	return 0;
}


double GetNum()
{
	char c;
	double res = 0;

	SkipSpaces();
	while (IsDigit(c = GetOper()))
		res = res * 10 + (c - '0');

	if (c == '.')
	{
		double dzielnik = 10;	//double dla dzielenia zmiennoprzecinkowego;
		while (IsDigit(c = GetOper()))
		{
			res += (c - '0') / dzielnik;
			dzielnik *= 10;
		}
	}

	ungetc(c, stdin);
	return res;
}


char GetOper()
{
	SkipSpaces();
	return getchar();
}


void SkipSpaces()
{
	char c;
	while ((c = getchar()) == ' ');
	ungetc(c, stdin);
}


double Calcul(char oper, double arg1, double arg2)
{
	switch (oper)
	{
	case '+':
		return arg1 + arg2;
	case '-':
		return arg1 - arg2;
	case '*':
		return arg1 * arg2;
	case '/':
		if (arg2 <= 1e-10)
		{
			printf("dzielenie przez 0\n");
			//return 0;				// Exception
		}
		return arg1 / arg2;
	case '^':
		return pow(arg1, arg2);
	default:
		printf("ERROR: blad operatora w funkcjii calcul\n");
		return 0;
	}
}






#endif


