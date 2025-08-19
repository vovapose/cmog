#include "../include/arrayOperations.h"

unsigned char**  InitializeArray(int RowsCount,int ColomsCount)

{
    unsigned char **din_array = (unsigned char**)calloc(RowsCount, sizeof(unsigned char*) ); 
    if (din_array == NULL) 
        printf("error in allocating memory for din_array colom");
    for(int i = 0; i < RowsCount; i++)
    {
        din_array[i] = (unsigned char*) calloc (ColomsCount,sizeof(unsigned char));
        if (din_array[i]  == NULL) 
            printf("error in allocating memory for din_array row");   
        for(int j = 0;j < ColomsCount; j++)
        {
            din_array[i][j] = (unsigned char) 0;
        }
    }
    return din_array;
}


char  MergeArray(unsigned char ** OldArray,unsigned char ** NewAray,int OldSize,int NewSize)
{
    if(OldSize > NewSize)
    {
        perror("Error: trying to merge bigger array with smaller. \n");
        return 1;         
    } 
    else if (((NewSize - OldSize) % 2 ) != 0)
    {
        perror("Error: the sizes of both matrices must either be even or odd ");
        return 1;
    }
    int Gap  = (NewSize - OldSize) / 2 ;
    for(int i = Gap;i <  NewSize - Gap;i++ ) 
    {
        for(int j = Gap;j < NewSize - Gap;j++)
        {
            NewAray[i][j] = OldArray[i - Gap][j - Gap];

        }
    }      
}
char  IsColomnEmpty(unsigned char ** array,int size,int colom)
{
    for (int i = 0;i < size;i++)
    {
        if(array[i][colom] != 0)
            return 0;
    }
    return 1;
}

char IsRowEmpty(unsigned char ** array,int size,int row)
{
    for (int i = 0;i < size;i++)
    {
        if(array[row][i] != 0)
            return 0;
    }
    return 1;
}
void DeleteArray(unsigned char ** array,int rows,int coloms)
{
    for(int i = 0;i < rows;i++)
    {
        free(array[i]);
    }
    free(array);

}

void PrintArray(unsigned char ** array,int RowsCount, int ColomsCount)
{
    for(int i = 0;i < RowsCount;i++)
    {
        for(int j  = 0;j < ColomsCount;j++)
        {
           printf("%d ", array[i][j]);
        }
        printf("\n");
    }
}



