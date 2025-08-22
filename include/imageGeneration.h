#ifndef IMAGEGENERATION_H
#define IMAGEGENERATION_H

#include <stdint.h>
#include <stdbool.h>

typedef struct 
{
    uint16_t r,g,b;
}pixel;

typedef struct 
{
    unsigned int rows;
    unsigned int cols;
    unsigned int maxval;

    pixel **pixels;
} ppmimage;

ppmimage * ppmReadImage(const char *filename);
void ppmDestroy(ppmimage * image);
bool ppmWriteImage(const char * filename,ppmimage * image);


#endif
