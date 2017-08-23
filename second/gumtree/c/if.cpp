#include "stdio.h"

void test()
{
    printf("begin");
    int i = 10;
    int j = 11;
    if (i == 1)
    {
        printf("1");
        printf("\t 2");
        i = 1;
    }
    else if(i == 3)
    {
        printf("3");
    }
    else
    {
        printf("others");
    }

    switch(i)
    {
        case 1:
          printf("1");
          break;
        case 3:
          printf("1");
          break;  
        default:
          printf("others");
          break;
    }

    for(i;i != 10; i++)
    {
      printf("%d", i);
    }

    while(i != 10)
    {
        i+= 1;
       printf("%d", i);
    }
    
    do
    {
        i+= 1;
       printf("%d", i);
    } while(i != 10);


    return;
}