#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

// ANSI color codes for boxed in letters
#define GREEN   "\e[30;42;1m"
#define YELLOW  "\e[30;43;1m"
#define RED     "\e[30;41;1m"
#define RESET   "\e[0;39m"

// declare list size
const int LISTSIZE = 1000;

// function prototype
char* generate_word(int wordsize);
void word_guess_cmp(char* wordle, char* guess, int wordsize);

int main(int argc, char* argv[])
{
    // // check to see if correct CLI arguments
    if (argc < 2)
    {
        printf("Usage: ./wordle wordsize\n");
        return 1;
    }
    
    // // convert wordsize to int
    int wordsize = atoi (argv[1]);

    // int wordsize = 8;

    // check to see if wordsize between 5 and 8
    if (wordsize < 5 || wordsize > 8)
    {
        printf("Error wordsize must be either 5, 6, 7, 8\n");
        return 2;
    }

    // create variable for guess
    char guess[wordsize];

    // create variable for wordle generated word
    char* wordle = malloc(sizeof(char) * wordsize);
    wordle = generate_word(wordsize);

    // compare wordle word and user guess
    word_guess_cmp(wordle, guess, wordsize);

    // free memory
    free(wordle);
    
    return 0;
}

// function defintion
char* generate_word(int wordsize)
{
    // get random line number
    srand(time(NULL));
    int random_line = 1 + rand() % LISTSIZE;

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

    // create variable to track line number
    int n = 0;

    // read a string until the end of file
    while (fgets(word, wordsize + 2, ptr) != NULL)
    {
        // increment line number
        n++;
        
        // if random line number = line number tracker, break
        if (n == random_line)
        {
            // printf("Wordle: %s\n", word);
            break;
        }
    }
    // return word as function output
    return word;

    // close and free files/memory
    fclose(ptr);
    free(word);
}

void word_guess_cmp(char* wordle, char* guess, int wordsize)
{
    // declare variables needed
    int letter_pos;
    int guess_count = 0;

    // array to check the status of the guess
    int status[wordsize];

    //populate array and set all numbers to zero
    for (int i = 0; i < wordsize; i++)
    {
        status[i] = 0;
    }
    
    // main loop in function to iterate through letters and check game status
    for (int k = 0; k < wordsize + 1; k++)
    {
        // variable to check for win
        int win = 0;

        // iterate through array to see current status
        for (int z = 0; z < wordsize; z++)
        {
            // if the letter does not equal 2, it's not in the correct space
            if (status[z] != 2)
            {
                // set it back to zero
                status[z] = 0;
            }
            else
            {
                // if letter is correct, add it to win variable
                win += status[z];
            }
        }

        // sense check that array is correctly populated after guessing
        for (int i = 0; i < wordsize; i++)
        {
            printf("%i", status[i]);
        }
        printf("\n");
        
        // checksum to see if game has been won
        if (win == (2 * wordsize))
        {
            printf(GREEN"Congratulations"RESET"\n");
            break;
        }

        // take input and ensure that strlen of guess is correct
        printf("Guess a %i letter word: ", wordsize);
        scanf("%s", guess);

        if (strlen(guess) != wordsize)
        {
            printf("Please input word of correct length\n");
            k--;
        }
        else
        {
            guess_count++;
            printf("Guess %i: ", guess_count);
        }

        // loop to check if the space is correct
        for (int i = 0; i < wordsize; i++)
        {
            // bool to check if guess[i] is in the correct space
            bool space = false;
            bool in_word = false;
            char correct_space;

            if (wordle[i] == guess[i])
            {
                space = true;
            }

            for (int j = 0; j < wordsize; j++)
            {
                if (wordle[j] == guess[i])
                {
                    in_word = true;
                }
            }

            if (space == true && in_word == true)
            {
                printf(GREEN"%c"RESET, guess[i]);
                status[i] = 2;
            }
            else if (space == false && in_word == true)
            {
                printf(YELLOW"%c"RESET, guess[i]);
                status[i] = 1;
            }
            else
            {
                printf(RED"%c"RESET, guess[i]);
            }
        }
        printf("\n");
    }
}