#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 256

int main(void)
{
    FILE *fp;
    fp = fopen("random50000.txt", "r");
    if (fp == NULL)
    {
        printf("Cannot open file\n");
        return 1;
    }

    int buffer;

    while (fscanf(fp, "%i", &buffer) == 1)
    {
        printf("%i\n", buffer);
    }
}