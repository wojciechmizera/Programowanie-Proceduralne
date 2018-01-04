#pragma once

#include "stdafx.h"

struct CharStack
{
	char key;
	CharStack* next;
};

void Push(CharStack** stos, char znak);
char Pop(CharStack** stos);
int IsEmpty(CharStack* stos);
void Del(CharStack** stos);
char Top(CharStack* stos);