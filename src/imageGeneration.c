#include "../include/imageGeneration.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <stddef.h>

ppmimage * ppmReadImage(const char *filename)
{
    FILE *file = fopen(filename, "rb");
    if(file == NULL)
    {
        perror("Error: could not open file");
        return NULL;
    
    }

    fseek(file,0,SEEK_END);
    size_t fileSize = ftell(file);

    int fileDS = fileno(file);


    rewind(file);    
    ppmimage * result = malloc(sizeof * result);



    char type[3] = {0};
    fscanf(file,"%2s",type);
    if (strcmp(type,"P6"))
    {
        perror("This is not a P6 ppm file");
        fclose(file);
        return NULL;
    }
    fscanf(file, "%u %u",&(result->cols),&(result->rows));
    fscanf(file, "%u",&(result->maxval));
    off_t offset = ftell(file);  
    uint8_t *rawdata = mmap(NULL,fileSize,PROT_READ,MAP_PRIVATE,fileDS,0);
    if (rawdata == MAP_FAILED)
    {
        perror("mmap: error");
        fclose(file);
        free(result);
        return NULL;
    }
    uint8_t bytesPerValue = (result->maxval > 256 ? 2 : 1);
    const int valuesPerPixel = 3;

    uint8_t *pixeldata = rawdata + offset + 1;

    result->pixels = calloc(result->rows, sizeof(pixel*));

        
    for(int y = 0;y < result->rows;y++)
    {
        result->pixels[y] = calloc(result->cols,sizeof(pixel));
        for(int x = 0;x < result->cols;x++)
        {
            uint8_t *pixelStart = pixeldata + (y * result->cols * valuesPerPixel * 
                    bytesPerValue) + (x * valuesPerPixel * bytesPerValue);
            if(bytesPerValue == 1)
            {
                result->pixels[y][x].r = pixelStart[0];
                result->pixels[y][x].g = pixelStart[1];
                result->pixels[y][x].b = pixelStart[2];
            }
            else
            {
                 result->pixels[y][x].r = (pixelStart[0] << 8) | pixelStart[1];
                 result->pixels[y][x].g = (pixelStart[2] << 8) | pixelStart[3];
                 result->pixels[y][x].b = (pixelStart[4] << 8) | pixelStart[5];
            }
        }
    }
    return result;
}

void ppmDestroy(ppmimage * image)
{
    for(int y = 0;y < image->rows;y++)
    {
        free(image->pixels[y]);
    }
    free(image);

}
bool ppmWriteImage(const char * filename,ppmimage * image)
{
    FILE *file = fopen(filename, "wb");
    if (file == NULL)
    {
        perror("Error: could not open file");
        return false;
    } 
    fprintf(file, "P6\n%u %u\n%u\n",image->cols,image->rows,image->maxval);
    uint8_t bytesPerValue = (image->maxval > 256 ? 2 : 1);
    for(int y = 0;y < image->rows;y ++)
    {
        for(int x = 0;x < image->cols;x ++)
        {
            fwrite(&(image->pixels[y][x].r),bytesPerValue,1,file);
            fwrite(&(image->pixels[y][x].g),bytesPerValue,1,file);
            fwrite(&(image->pixels[y][x].b),bytesPerValue,1,file);
        }
    }
    return true;
}

ppmimage * ppmCreate(unsigned int cols,unsigned int rows,unsigned int maxval)
{
    ppmimage * img = malloc(sizeof(ppmimage));
    if (img == NULL) 
    {
        perror("Error: could not alocate memory for img");
    }
    img->cols = cols;
    img->rows = rows;
    img->maxval = maxval;
    img->pixels = calloc(rows,sizeof(ppmimage*));
    if(img->pixels == NULL)
    {
        perror("Error: cound not alocate memory for img pixel array");
    }
    for(unsigned int y =  0;y < rows;y ++ )
    {
        img->pixels[y] = calloc(cols,sizeof(pixel ));
        if(img->pixels[y] == NULL)
        {
            perror("Error: cound not alocate memory for img row");
        }
    }
    return img;
}

