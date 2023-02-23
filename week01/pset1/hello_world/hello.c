#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
     char *string = malloc(sizeof(char) * strlen(string));
     printf("What is your name: ");
     scanf("%s", string);
     printf("Hello, %s\n", string);
}