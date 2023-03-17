#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// global variables
int byte = 8;
int max = 256;

// function prototypes
void reverseArray(int array[], int bits);
void print_bulb(int bit);

int main(void)
{
    // create variable for message
    char *message = malloc(sizeof(char) * max);

    // prompt user for a secret word
    printf("What is your secret word: ");
    fgets(message, max, stdin);

    // create array varable for string of bits
    int array[byte];

    // temp variable for integer value of character
    int c;

    // iterate through each character of string
    for (int i = 0; i < strlen(message); i++)
    {
        // assign integer value of character to c
        c = message[i];

        // loop to populate array
        for (int j = 0; j < byte; j++)
        {
            array[j] = c % 2;
            c /= 2;
        }

        // reverse the array of bits to get binary number
        reverseArray(array, byte);

        // print out each bit
        for (int k = 0; k < byte; k++)
        {
            print_bulb(array[k]);
        }
        printf("\n");
    }

    // free allocated memory
    free(message);
    
    return 0;
}

// function definition
void reverseArray(int array[], int bits)
{
    int temp = 0;
    for (int i = 0; i < byte / 2; i++)
    {
        temp = array[i];
        array[i] = array[byte - i - 1];
        array[byte - i - 1] = temp;
    }
}

// function definition
void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}