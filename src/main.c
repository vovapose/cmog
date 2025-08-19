#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "../include/arrayOperations.h"

#define INITIALSIZE 16
unsigned int ChouseRandoms(int min,int max);
void StartGeneration (unsigned char  ** array, int size,unsigned char percenteToFill);
unsigned char FindPosition(unsigned char ** array, int size, int numToFind );

char  RandomMovement(unsigned char ** array,int size,int * numToMoveAround);
signed char  IsThereNeighbour(unsigned char ** array,int size,int * numToSearchAround);
signed char LocationOfConnection(unsigned char ** array,int size,int * numToSearchAround);
unsigned char **  MakeGapsAndFill(unsigned char ** array,int size,unsigned char ** pItArray,int pItArraySize);
void CopyCol(unsigned char ** arrayDest,int sizeD,int colomD,int rowToStartD,unsigned char ** arraySource,int sizeS,int colomS,int rowToStartS);
void CopyRow(unsigned char ** arrayDest,int sizeD,int colomToStartD,int rowD,unsigned char ** arraySource,int sizeS,int colomToStartS,int rowS);
void FillVerticaly(unsigned char ** array,int size,int colom);
void FillHorizontaly(unsigned char ** array,int size,int row);


void MoveColBack(unsigned char ** array,int size,int colom,signed char lenghth);
int  main(void)
{
    unsigned char  ** array;
    unsigned char  ** nItArray;
    int size = INITIALSIZE;
    array = InitializeArray(INITIALSIZE,INITIALSIZE);
    
    FindPosition(array,INITIALSIZE,37);
    StartGeneration(array,INITIALSIZE,10);
    printf("new array");
    nItArray = InitializeArray(INITIALSIZE * 2,INITIALSIZE * 2);
    printf("merge \n");
     
    //MergeArray(array,nItArray,INITIALSIZE,INITIALSIZE * 2); 
    //PrintArray(nItArray,INITIALSIZE * 2,INITIALSIZE *2 );
    array = MakeGapsAndFill(nItArray,INITIALSIZE * 2,array,INITIALSIZE);
    PrintArray(array,INITIALSIZE * 2,INITIALSIZE *2);
    StartGeneration(array,INITIALSIZE * 2,10);
    PrintArray(array,INITIALSIZE * 2,INITIALSIZE * 2);
     //FindPosition(array,10,54);
    sleep(1);


    while (getchar() != '\n')

    return 0;
}

unsigned char  FindPosition(unsigned char ** array,int size,int numToFind)
{
    printf("start postition\n");
    int counter = 0;
    for(int i = 0;i < size;i++)
    {
        for(int j  = 0;j < size;j++)
        {
            
            if (counter == numToFind && array[i][j] == 0)
            {
               
                array[i][j] = 1;
                PrintArray(array,size,size);
                return 0;
            
            }
            counter ++;

        }
    }
    
    return 1;
}
unsigned int ChouseRandoms(int min, int max) 
{
  
    // Open the file urandom
    int fd = open("/dev/urandom", O_RDONLY);

    // Print the random number
    //printf("Random numbers between %d and %d: ", min, max);

    // Generate a random number
    unsigned int rd_num;
    read(fd, &rd_num, sizeof(rd_num));

    // Scale the random value to the range [min, max]
    rd_num = rd_num % (max - min + 1) + min;
   
    // close the file
    close(fd);
    printf ("%d \n",rd_num);
    return rd_num;
}

unsigned char **  MakeGapsAndFill(unsigned char ** array,int size,unsigned char ** pItArray,int pItArraySize)
{

    int gap  = (size - size / 2) / 2;
    int startPoint = gap;
    for(int i = 0;i < pItArraySize;i ++)
    {
        if(IsColomnEmpty(pItArray,i,pItArraySize) == 0)
        {
            CopyCol(array,size,startPoint,gap,pItArray,pItArraySize,i,0);
            FillHorizontaly(array,size,startPoint);
            startPoint += 2;
        }
        
    
    }
    DeleteArray(pItArray,pItArraySize,pItArraySize);   
    pItArray = InitializeArray(pItArraySize * 2,pItArraySize * 2);
    startPoint = gap;
    for(int i = 0;i < pItArraySize * 2;i ++)
    {
        if(IsRowEmpty(array,i,size) == 0)
        {
            CopyRow(pItArray,pItArraySize,0,startPoint,array,size,0,i);
            FillVerticaly(pItArray,pItArraySize * 2,startPoint);
            startPoint += 2;
        }

    }
    return pItArray;
}


void FillVerticaly(unsigned char ** array,int size,int row)
{
   for(int i = 0;i < size - 1 ;i++)
   
   {
        if(array[row][i] == 0)
            continue;
        else if (array[row][i] == 1)
        {

            array[row + 1 ][i] = 1;
        }
        else if(array[row][i] == 3)
            array[row - 1][i] = 3;
        
   }
}
void FillHorizontaly(unsigned char ** array,int size,int colom)
{
    for(int i = 0;i < size - 1;i++)
    {
        if(array[i][colom] == 0)
            continue;
        else if (array[i][colom] == 2)
            array[i][colom - 1] = 2;
        else if(array[i][colom] == 4)
            array[i][colom + 1] = 4; 
    }
}

void MoveColBack(unsigned char ** array,int size,int colom,signed char lenghth)
{
    int i = 0;
     
    do
    {
     
        array[i][colom - lenghth] = array[i][colom];
        array[ i][colom] = 0;
        i++;


    }while(i != size);

    
}
void CopyRow(unsigned char ** arrayDest,int sizeD,int colomToStartD,int rowD,
        unsigned char ** arraySource,int sizeS,int colomToStartS,int rowS)
{
    if((sizeD - colomToStartD) >  sizeS && sizeD != sizeS)
    {
        perror("Error: row from Source is too big for Destination \n");
        //to do make errors processing and not exit
        exit(1);
    }
    for(int i = 0;i < sizeS;i++)
    {
        arrayDest[rowD][colomToStartD + i] = arraySource[rowS][colomToStartS + i];
        //printf("%d" , );        
    }
}
void CopyCol(unsigned char ** arrayDest,int sizeD,int colomD,int rowToStartD,
        unsigned char ** arraySource,int sizeS,int colomS,int rowToStartS)
{
    if((sizeD - rowToStartD) <  sizeS && sizeD != sizeS)
    {
        perror("Error: colom from Source is too big for Destination \n");
        //to do make errors processing and not exit
        exit(1);
    }
    for(int i = 0;i < sizeS;i++)
    {
        arrayDest[rowToStartD + i][colomD] = arraySource[rowToStartS + i][colomS];
        //printf("%d" , );        
    }
}
void StartGeneration(unsigned char ** array, int size,unsigned char percenteToFill)
{
    printf("start generaion \n" );
    register unsigned int *randomNumb = (unsigned int *)malloc(sizeof(unsigned int));
    register int checkSum;
    unsigned char counter = 0;
    signed char checker = 0;
    checkSum = (percenteToFill * (size * size)) / 100;
    while(counter < checkSum)
    {
        * randomNumb = ChouseRandoms(0,size * size - 1);
       if(FindPosition(array,size,*randomNumb))
           continue;
       if (IsThereNeighbour(array,size,randomNumb) == -1)
       {
           array[*randomNumb / size][ * randomNumb % size] = 0;
           continue;
       }
       while(IsThereNeighbour(array,size,randomNumb) == 0)
       {
               
             
           if(RandomMovement(array,size,randomNumb) == 0)
           {

                array[*randomNumb / size][*randomNumb % size] = 0;

                counter--;

                break;

           }

       }
       if (IsThereNeighbour(array,size,randomNumb) == -1)
       {
           array[*randomNumb / size][ * randomNumb % size] = 0;
           continue;
       }
       LocationOfConnection(array,size,randomNumb);
       counter++;
    }   
    printf("stop generation \n");
}

signed char  IsThereNeighbour(unsigned char **array, int size, int *numToSearchAround)
{
    printf("start neighb\n %d\n",*numToSearchAround );
    //PrintArray(array,size,size);
    int row;
    int colom;
    row = * numToSearchAround / size;
    colom = * numToSearchAround % size;
    if( (((row + 1) % size) == 0) ||( (row - 1) < 0 )|| ((colom + 1) % size == 0) || ((colom - 1)<0))
    {
        return -1;
    }
    else if ((array[(row + 1)][colom]  != 0) || (array[(row - 1)][colom]  != 0)||
(array[row][(colom - 1)]  != 0 )||  (array[row][(colom + 1)]   != 0))
    {
        return 1;
    }   
    return 0;
    printf("stop neighb\n");

}

signed char LocationOfConnection(unsigned char ** array,int size,int *numToSearchAround)
{
    int  row = * numToSearchAround / size;
    int colom = * numToSearchAround % size;  
    if(array[row+1][colom] != 0)
    {

      array[row][colom] = 0;
      array[(row)][colom] = 1;

    }
    else  if(array[row][colom - 1] != 0)
    {

      array[row][colom] = 0;
      array[(row)][colom] = 2;
    }    
    else if(array[row-1][colom] != 0)
    {

      array[row][colom] = 0;
      array[(row)][colom] = 3;

    }
    else if(array[row][colom+1] != 0)
    {

      array[row][colom] = 0;
      array[(row)][colom] = 4;

    }

}

char RandomMovement(unsigned char ** array,int size,int * numToMoveAround)
{
    printf("start rndm \n");
    int row;
    int colom;
    signed char random;
    row = * numToMoveAround/size;
    colom = * numToMoveAround % size;
    if( (((row + 1) % size) == 0) ||( (row - 1) < 0 )|| ((colom + 1) % size == 0) || ((colom - 1)<0))
    {
        return 0;
    }
    random = ChouseRandoms(1,4);
    switch(random)
    {
        case(1):
            array[row][colom] = 0;
            array[(row + 1)][colom] = 1;
            * numToMoveAround += size;            
            break;
        case(2):
            array[row][colom] = 0;
            array[row][(colom - 1)] = 1;
            * numToMoveAround -= 1;
            break;
        case(3):
            array[row][colom] = 0;
            array[(row -  1)][colom] = 1;
            * numToMoveAround -= size;
            break;
        case(4):
            array[row][colom] = 0;
            array[row][(colom + 1)] = 1;
            * numToMoveAround += 1;
            break; 
        default:
            printf("bro wherer tf are you");
            break;
    } 
    printf("stop rndm \n");
    return 1;
} 


