#ifndef ARRAYOPERATIONS_H
#define ARRAYOPERATIONS_H

#include <stdlib.h>
#include <stdio.h>
unsigned char ** InitializeArray(int RowsCount,int ColomsCount);
void DeleteArray(unsigned char ** array,int rows,int coloms);
void PrintArray(unsigned char ** array,int RowsCount, int ColomsCount);
char  MergeArray(unsigned char ** OldArray,unsigned char ** NewAray,int OldSize,int NewSize);
char IsColomnEmpty(unsigned char ** array,int colom,int size);
char IsRowEmpty(unsigned char ** array,int row,int size);



#endif 
