#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// index = 0.0588 * L - 0.296 * S - 15.8
// L = the average number of letters per 100 words in the text
// S = the average number of sentences per 100 words in the text

#define MAX 500

// function prototype
void grade(int letters, int sentences, int words);

int main(void)
{
    // variables
    int words = 1;
    int letters = 0;
    int sentences = 0;

    // prompt user for text
    printf("Text: ");

    // assign text to string variable
    char text[MAX];
    fgets(text, MAX, stdin);

    // variable for length of string
    int len = strlen(text);

    // iterate through string
    for (int i = 0; i < len; i++)
    {
        // count words
        if (text[i] == 32)
        {
            words++;
        }
        // count letters
        else if (isalpha(text[i]))
        {
            letters++;
        }
        // count sentences
        else if (text[i] == 33 || text[i] == 46 || text[i] == 63)
        {
            sentences++;
        }
    }

    // call function
    grade(letters, sentences, words);
}

// function definition
void grade(int letters, int sentences, int words)
{
    // to get average:
    float L = (float)letters / words * 100;
    float S = (float)sentences / words * 100;

    // index = 0.0588 * L - 0.296 * S - 15.8
    float index = 0.0588 * L - 0.296 * S - 15.8;

    // round to closest integer
    int grade = round(index);

    // print out grade
    if (grade > 16)
    {
        printf("Grade 16+\n");
    }
    else if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}