#include <malloc.h>
#include "StosOperatorow.h"

void Push(CharStack** stos, char znak)
{
	CharStack* nowy = (CharStack*)malloc(sizeof(CharStack));
	memset(nowy, 0, sizeof(nowy));
	nowy->key = znak;
	nowy->next = *stos;
	*stos = nowy;
}


char Pop(CharStack** stos)
{
	char c = 0;
	if (!IsEmpty(*stos))
	{
		c = Top(*stos);
		Del(stos);
	}
	else
		printf("Error(Pop()<oper>) Stack underflow");
	return c;
}


int IsEmpty(CharStack* stos)
{
	return !stos;
}


void Del(CharStack** stos)
{
	if (IsEmpty(*stos))
	{
		printf("ERROR(Del<oper>) Stack Underflow\n");
	}
	else
	{
		CharStack* temp = *stos;
		*stos = temp->next;
		free(temp);
	}
}


char Top(CharStack* stos)
{
	if (IsEmpty(stos))
	{
		//printf("ERROR(Top<oper> Stack underflow)");			// 
		return 0;
	}
	return stos->key;
}
