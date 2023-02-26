#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// declare list size
const int LISTSIZE = 10;

// function prototype
char* generate_word(int wordsize);
void word_guess_cmp(char* word, char* guess);

int main(void)
{
    // // check to see if correct CLI arguments
    // if (argc < 2)
    // {
    //     printf("Usage: ./wordle wordsize");
    //     return 0;
    // }

    // // convert wordsize to int
    // int wordsize = atoi (argv[1]);

    // // // check to see if wordsize between 5 and 8
    // if (wordsize < 5 || wordsize > 8)
    // {
    //     printf("Error wordsize must be either 5, 6, 7, 8\n");
    //     return 2;
    // }

    int wordsize = 5;
    // create variable for guess
    char guess[wordsize];

    // take input and assign to guess
    // printf("Guess a %i letter word: ", wordsize);
    // scanf("%s", guess);
    // printf("%s\n", guess);

    char* wordle = malloc(sizeof(char) * wordsize);
    wordle = generate_word(wordsize);

    // printf("%s\n", wordle);
    free(wordle);
    
    return 0;
}

// function defintion
char* generate_word(int wordsize)
{
    // get random line number
    srand(time(NULL));
    int random_line = rand() % LISTSIZE;

    // create file pointer and check to see if NULL
    FILE *ptr;
    if (ptr == NULL)
    {
        printf("File cannot be opened\n");
    }

    // create string to see what text file to open
    char str[6];

    // sprintf name of file to str variable
    sprintf(str, "%i.txt", wordsize);

    // open text file
    ptr = fopen(str, "r");

    // create word variable
    char *word = malloc(sizeof(char) * wordsize);
    for (int i = 0; i < LISTSIZE; i++)
    {
        fgets(word, wordsize + 1, ptr);
        printf("%s", word);
    }
    fclose(ptr);
    return word;
}

void word_guess_cmp(char* word, char* guess)
{

}