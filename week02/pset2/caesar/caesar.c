#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

int max = 246;

int main(int argc, char *argv[])
{
    // alphabet array
    char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    // ensure correct amount of commands
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // ensure key only has integers
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (isdigit(argv[1][i]) == false)
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    // convert key to integer value
    int key = atoi(argv[1]);

    // string variable to hold plaintext
    char *plaintext = malloc(sizeof(char) * max);

    // prompt user for plaintext
    printf("plaintext: ");
    fgets(plaintext, max, stdin);

    // variable to hold length of plaintext
    int msgLen = strlen(plaintext);

    // prepare to print plaintext
    printf("ciphertext: ");

    // loop to print out characters with key value added
    for (int i = 0; i < msgLen; i++)
    {
        int n = 0;

        // loop to find the location of plaintext[i] in alphabet
        for (int j = 0; j < strlen(alphabet); j++)
        {
            if (plaintext[i] == alphabet[j] || plaintext[i] == alphabet[j] - 32 || plaintext[i] == alphabet[j] + 32)
            {
                n = j;
            }
        }

        // position of new character after algorithm
        int newCharPos = (n + key) % 26;

        // print statements 
        if (isalpha(plaintext[i]))
        {
            // match case
            if (isupper(plaintext[i]))
            {
                printf("%c", alphabet[newCharPos]);
            }
            else
            {
                printf("%c", tolower(alphabet[newCharPos]));
            }
        }
        else
        {
            printf("%c", plaintext[i]);
        }
    }
    
    // free allocated memory and end program
    free(plaintext);
    return 0;
}