#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        printf("Usage: ./wordle wordsize");
        return 0;
    }

    int wordsize = atoi (argv[1]);

    if (wordsize < 5 || wordsize > 8)
    {
        printf("Error wordsize must be either 5, 6, 7, 8\n");
        return 2;
    }

    char guess[wordsize];

    printf("Guess a %i letter word: ", wordsize);
    scanf("%s", guess);
    printf("%s\n", guess);
    
    return 0;
}