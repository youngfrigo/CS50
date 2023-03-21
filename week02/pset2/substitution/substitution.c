#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// example key: VCHPRZGJNTLSKFBDQWAXEUYMOI

// global variable for length of key
int keyLen = 26;

// function prototype
int checkDuplicate(int keyLength, char *key);
void encrypt(int messageLength, int keyLength, char *key, char *plaintext);

int main(int argc, char *argv[])
{
    // create array for key
    char key[keyLen];

    // ensure there are two CLI commands
    if (argc != 2)
    {
        printf("Usage: ./substitution key");
        return 1;
    }

    // ensure that length of key is 26 characters
    else if (strlen(argv[1]) != 26)
    {
        printf("Key must be 26 characters long");
        return 1;
    }

    // load argv[1] into key array
    for (int i = 0; i < keyLen; i++)
    {
        key[i] = argv[1][i];
    }

    // ensure no duplicates in key
    if (checkDuplicate(keyLen, key) == 1)
    {
        return 1;
    }

    // prompt user for their message
    char *plaintext = malloc(sizeof(char) * 256);
    printf("plaintext: ");
    fgets(plaintext, 256, stdin);

    // variable for message length
    int len = strlen(plaintext);

    // prepare stdout for ciphertext
    printf("ciphertext: ");

    // main function to encrypt message
    encrypt(len, keyLen, key, plaintext);

    // end program
    return 0;
}

// function definition
int checkDuplicate(int keyLength, char *key)
{
    // variable to track duplicates
    int charTracker = 0;
    for (int i = 0; i < keyLength; i++)
    {
        if (keyLen < 26)
        {
            return 1;
        }
        // if character not encountered twice, reset
        charTracker = 0;
        for (int j = 0; j < keyLen; j++)
        {
            // increment if letter is encountered
            if (key[i] == key[j])
            {
                charTracker++;
            }
        }
        // return 1 if letter encountered twice
        if (charTracker == 2)
        {
            printf("Characters cannot be repeated in key\n");
            return 1;
        }
        // return 1 if character is invalid
        else if (isalpha(key[i]) == false)
        {
            printf("Key cannot contain invalid characters\n");
            return 1;
        }
    }
    // if nothing is triggered return true
    return 0;
}

// function definition
void encrypt(int messageLength, int keyLength, char *key, char *plaintext)
{
    char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    // iterate over each character of the message
    for (int i = 0; i < messageLength; i++)
    {
        // loop to compare character of plaintext to key
        for (int j = 0; j < keyLength; j++)
        {
            // if characters match regardless of case, print relevant character
            if (plaintext[i] == alphabet[j] || plaintext[i] == (alphabet[j] - 32) || plaintext[i] == (alphabet[j] + 32) || plaintext[i] == 32)
            {
                // print uppercase letter
                if (isupper(plaintext[i]))
                {
                    printf("%c", toupper(key[j]));
                }
                // print lowercase letter
                else if (islower(plaintext[i]))
                {
                    printf("%c", tolower(key[j]));
                }
                // if character is a space, print as such then break current loop to move on to the next character in the plaintext
                else if (plaintext[i] == 32)
                {
                    printf("%c", plaintext[i]);
                    break;
                }
                // otherwise print without any changes
                else
                {
                    printf("%c", plaintext[i]);
                }
            }
        }
    }
    printf("\n");
}