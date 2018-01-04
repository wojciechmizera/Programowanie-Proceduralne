// stdafx.cpp : source file that includes just the standard includes
// $safeprojectname$.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

// TODO: reference any additional headers you need in STDAFX.H
// and not in this file
//
//double ONP()
//{
//	char oper;
//	StosOperatorow* listaOper = NULL;
//	StosLiczb* listaLiczb = NULL;
//
//	while ((oper = GetOper()) == '(')
//		Push(&listaOper, oper);
//
//	ungetc(oper, stdin);
//
//	Push(&listaLiczb, GetNum());
//	while (IsOper(oper = GetOper()))
//	{
//		if (oper == ')')
//		{
//			while ((oper = Pop(&listaOper)) != '(')
//			{
//				double x = Pop(&listaLiczb);
//				Push(&listaLiczb, Calcul(oper, Pop(&listaLiczb), x));
//			}
//		}
//		else
//		{
//			while (Prior(oper) <= Prior(Top(listaOper)) && oper != '(')
//			{
//				double x = Pop(&listaLiczb);
//				Push(&listaLiczb, Calcul(Pop(&listaOper), Pop(&listaLiczb), x));
//			}
//
//			Push(&listaOper, oper);
//
//			oper = GetOper();
//			ungetc(oper, stdin);
//
//			if (IsDigit(oper))
//			{
//				Push(&listaLiczb, GetNum());
//			}
//		}
//	}
//
//	while (!IsEmpty(listaOper))
//	{
//		double x = Pop(&listaLiczb);
//		Push(&listaLiczb, Calcul(Pop(&listaOper), Pop(&listaLiczb), x));
//	}
//
//	return Pop(&listaLiczb);
//}
//
//
//int IsOper(char znak)
//{
//	switch (znak)
//	{
//	case '(':
//	case ')':
//	case '+':
//	case '-':
//	case '*':
//	case '/':
//	case '^':
//		return 1;
//	}
//	return 0;
//}
//
//
//int IsDigit(char c)
//{
//	return (c >= '0') && (c <= '9');
//}
//
//
//int Prior(char znak)
//{
//	switch (znak)
//	{
//	case '(':
//		return 0;
//	case '+':
//	case '-':
//	case ')':				//tego chyba nie musi byc
//		return 1;
//	case '*':
//	case '/':
//		return 2;
//	case '^':
//		return 3;
//	}
//	return 0;
//}
//
//
//double GetNum()
//{
//	char c;
//	double res = 0;
//
//	SkipSpaces();
//	while (IsDigit(c = GetOper()))
//		res = res * 10 + (c - '0');
//
//	if (c == '.')				// ew makrodefinicja
//	{
//		double dzielnik = 10;	//double dla dzielenia zmiennoprzecinkowego;
//		while (IsDigit(c = GetOper()))
//		{
//			res = res + (c - '0') / dzielnik;
//			dzielnik *= 10;
//		}
//	}
//
//	ungetc(c, stdin);
//	return res;
//}
//
//
//char GetOper()
//{
//	SkipSpaces();
//	return getchar();
//}
//
//
//void SkipSpaces()
//{
//	char c;
//	while ((c = getchar()) == ' ');
//	ungetc(c, stdin);
//}
//
//
//double Calcul(char oper, double arg1, double arg2)
//{
//	switch (oper)
//	{
//	case '+':
//		return arg1 + arg2;
//	case '-':
//		return arg1 - arg2;
//	case '*':
//		return arg1 * arg2;
//	case '/':
//		if (arg2 <= 1e-10)			// bo double, wiec nigdy nie wiadomo, 
//		{							// przesadna ostroznosc troche
//			printf("dzielenie przez 0\n");
//			//return 0;				// mozna tak, ale to jeszcze bardziej miesza
//		}
//		return arg1 / arg2;
//	case '^':
//		return pow(arg1, arg2);
//	default:
//		printf("ERROR: blad operatora w funkcjii calcul\n");
//		return 0;
//	}
//}
//
