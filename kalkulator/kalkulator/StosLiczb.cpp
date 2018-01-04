#include "StosLiczb.h"
#include <malloc.h>

void Push(IntStack** stos, double liczba)
{
	IntStack* nowy = (IntStack*)malloc(sizeof(IntStack));
	memset(nowy, 0, sizeof(nowy));
	nowy->key = liczba;
	nowy->next = *stos;
	*stos = nowy;
}


double Pop(IntStack** stos)
{
	double x = 0;
	if (!IsEmpty(*stos))
	{
		x = Top(*stos);
		Del(stos);
	}
	else
		printf("ERROR(Pop<number>) Stack underflow\n");
	return x;
}


int IsEmpty(IntStack* stos)
{
	return !stos;
}


void Del(IntStack** stos)
{
	if (IsEmpty(*stos))
	{
		printf("ERROR(isEmpty<number>) Stack Underflow\n");
	}
	else
	{
		IntStack* temp = *stos;
		*stos = temp->next;
		free(temp);
	}
}


double Top(IntStack* stos)
{
	if (IsEmpty(stos))
	{
		//printf("ERROR(top<number>) stack underflow\n");
		return 0;
	}
	return stos->key;
}

