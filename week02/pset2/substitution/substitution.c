#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max = 256;
int keyLen = 26;

int main(int argc, char* argv[])
{
    // create arrays for alphabet and key
    char alphabet[] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
    char key[strlen(argv[1])];

    for (int i = 0; i < keyLen; i++)
    {
        key[i] = argv[1][i];
    }

    char* plaintext = malloc(sizeof(char) * max);
    char* cyphertext = malloc(sizeof(char)* max);

    if (argc == 1)
    {
        printf("Usage ./substitution key\n");
        return 1;
    }
    else if (strlen(argv[1]) != keyLen)
    {
        printf("Key must have 26 characters\n");
        return 1;
    }

    printf("Plaintext: ");
    fgets(plaintext, max, stdin);
    printf("%s\n", plaintext);

    // variable for message length
    int msgLen = strlen(plaintext);

    printf("Cyphertext: ");

    // iterate through the message
    for (int i = 0; i < msgLen; i++)
    {
        // compare with the alphabet to find location
        for (int j = 0; j < keyLen; j++)
        {
            if (isalpha(plaintext[i] != 1))
            {
                printf("%c", plaintext[i]);
            }
            if (plaintext[i] == alphabet[j])
            {
                cyphertext[i] = key[j];
            }
        }
    }
    printf("\nmsgLen: %i, keyLen: %i\n", msgLen, keyLen);

    // print out the character at that position of the key
    // if the character in the message is not alphabetic, print without changing
    // if alphabetic, fork between uppercase and lowercase so that the cases match between plaintext and cyphertext 
    free(plaintext);
    free(cyphertext);

    return 0;
}