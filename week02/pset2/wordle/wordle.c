#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// declare list size
const int LISTSIZE = 1000;

// function prototype
char* generate_word(int wordsize);
void word_guess_cmp(char* word, char* guess);

int main(int argc, char* argv[])
{
    // check to see if correct CLI arguments
    if (argc < 2)
    {
        printf("Usage: ./wordle wordsize");
        return 0;
    }

    // convert wordsize to int
    int wordsize = atoi (argv[1]);

    // check to see if wordsize between 5 and 8
    if (wordsize < 5 || wordsize > 8)
    {
        printf("Error wordsize must be either 5, 6, 7, 8\n");
        return 2;
    }

    // create variable for guess
    char guess[wordsize];

    // take input and assign to guess
    printf("Guess a %i letter word: ", wordsize);
    scanf("%s", guess);
    printf("%s\n", guess);

    char* wordle = malloc(sizeof(char) * wordsize);
    wordle = generate_word(wordsize);

    printf("%s", wordle);
    
    return 0;
}

// function defintion
char* generate_word(int wordsize)
{
    // get random line number
    srand(time(NULL));
    int random_line = rand() % 1000;

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

    // variable to track line number
    int n = 0;

    // while loop to check every line
    while (fgets(word, sizeof(word) + 1, ptr) != NULL)
    {
        // increment line number in every iteration of while loop
        n++;

        // check to see if random line number is the same
        // print word read from file and line number
        if (n == random_line)
        {
            printf("%i\n", random_line);
        }

        // once end of file is reached, break the loop
        if (fgets(word, sizeof(word) + 1, ptr) == NULL)
        {
            break;
        }
    }
    fclose(ptr);
    return word;
    free (word);
}

void word_guess_cmp(char* word, char* guess)
{

}