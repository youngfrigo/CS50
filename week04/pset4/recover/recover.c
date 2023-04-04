#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    FILE *fp = fopen("card.raw", "r");
    if (fp == NULL)
    {
        printf("Could not open file\n");
        return 1;
    }
    
    return 0;
}