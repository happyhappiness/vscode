#include <stdio.h>
#include "DumpInformation.h"

int DumpFile(char* filename, char* comment)
{
  FILE* file = fopen(filename, "r");
  if(!file)
    {
    printf("Error, could not open file %s\n", filename);
    return 1;
    }
  printf("%s", comment);
  while(!feof(file))
    {
    int ch = fgetc(file);
