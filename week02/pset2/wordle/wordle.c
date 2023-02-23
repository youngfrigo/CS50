#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* generate_word(void);

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

    generate_word();
    
    return 0;
}

char* generate_word(void)
{
    FILE* ptr;
    char* word;
    ptr = fopen("5-letter.txt", "r");

    if (ptr == NULL)
    {
        printf("File cannot be opened\n");
    }
    
    word = fgets(word, 5, ptr);
    printf("%s\n", word);

    return word;
}