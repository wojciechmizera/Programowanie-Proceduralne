#pragma once
#include "defs.h"

int  ReadData(LottoPlayer*** pAllDraws, const char* sfileName);

void CalcStat50(int* pNums, LottoPlayer** pDraws, int nDrawsNo);
void CalcStat10(int* pNums, LottoPlayer** pDraws, int nDrawsNo);

int CompareNames(const void* p1, const void* p2);

void FreeMem(LottoPlayer** pTab, int nDrawsNo);
void HeapCheck();