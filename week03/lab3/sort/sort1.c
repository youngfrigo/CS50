#include <stdio.h>
#include <stdlib.h>

int listsize = 20;

int main(void)
{
    int buffer[listsize];

    FILE *fp = fopen("random5000.txt", "r");
    if (fp == NULL)
    {
        printf("File could not be opened\n");
        return 1;
    }

    fread(buffer, sizeof(int), 1, fp);
    for (int i = 1; i <= listsize; i++)
    {
        printf("%i\n", buffer[i]);
        fread(buffer, sizeof(int), 1, fp);
    }

    fclose(fp);
}