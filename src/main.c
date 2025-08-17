#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "../include/arrayOperations.h"

unsigned int ChouseRandoms(int min,int max);
void StartGeneration (unsigned char  ** array, int size,unsigned char percenteToFill);
unsigned char FindPosition(unsigned char ** array, int size, int numToFind );

char  RandomMovement(unsigned char ** array,int size,int * numToMoveAround);
int  IsThereNeighbour(unsigned char ** array,int size,int * numToSearchAround);

int  main(void)
{
//   InitWindow(800, 450, "raylib [core] example - basic window");
//
//      while (!WindowShouldClose())
//   {
//      
//        BeginDrawing();
//            ClearBackground(RAYWHITE);
//            DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);///       EndDrawing();
//    }
    unsigned char  ** array;
    array = InitializeArray(10,10);
    PrintArray(array,10,10);
    FindPosition(array,10,54);
    sleep(1);
    StartGeneration(array,10,20);
    PrintArray(array,10,10);
    unsigned char ** NewAray;
    NewAray = InitializeArray(14,14);
    MergeArray(array,NewAray,10,14);  


    PrintArray(NewAray,14,14);
    StartGeneration(NewAray,14,30);
    while (getchar() != '\n')
//   CloseWindow();

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
            
            if (counter == numToFind && array[i][j] != 1)
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
unsigned int ChouseRandoms(int min, int max) {
  
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

void StartGeneration(unsigned char ** array, int size,unsigned char percenteToFill)
{
    printf("start generaion \n" );
    unsigned int *randomNumb = (unsigned int *)malloc(sizeof(unsigned int));
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
           counter++;
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
           counter++;
           continue;
       }
       counter++;
    }   
    printf("stop generation \n");
}

int  IsThereNeighbour(unsigned char **array, int size, int *numToSearchAround)
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
    else if ((array[(row + 1)][colom]  == 1) || (array[(row - 1)][colom]  == 1)||
(array[row][(colom - 1)]  == 1 )||  (array[row][(colom + 1)]   == 1))
    {
        return 1;
    }   
    return 0;
    printf("stop neighb\n");
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


