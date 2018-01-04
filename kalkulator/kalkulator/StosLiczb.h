#pragma once


#include "stdafx.h"


struct IntStack
{
	double key;
	IntStack* next;
};

void Push(IntStack** stos, double liczba);
double Pop(IntStack** stos);
int IsEmpty(IntStack* stos);
void Del(IntStack** stos);
double Top(IntStack* stos);