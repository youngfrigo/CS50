#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

// created data types and block define
typedef char* string;
typedef uint8_t BYTE;
#define BLOCK 512

// required variables
BYTE buffer[BLOCK];
char filename[32];
FILE* f_out;
int jpgCount = 0;
bool jpgFound;

int main(void)
{
    // open memory card and error check
    FILE* fp = fopen("card.raw", "rb");
    if (fp == NULL)
    {
        printf("Could not open file\n");
        return 1;
    }

    // loop through the entire file
    while (!feof(fp))
    {
        // read 512 bytes into buffer
        fread(buffer, sizeof(BYTE), BLOCK, fp);

        // JPG signature check
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && ((buffer[3] & 0xf0) == 0xe0))
        {  
            // close if a jpg has already been found
            if (jpgCount > 0)
            {
                fclose(f_out);
            }

            // open a new jpg file and error check
            sprintf(filename, "%03i.jpg", jpgCount);
            f_out = fopen(filename, "wb");
            if (f_out == NULL)
            {
                printf("Could not open file to write to\n");
                return 2;
            }

            // write jpg signature to current file and increment count
            fwrite(buffer, sizeof(BYTE), BLOCK, f_out);
            jpgCount++;
        }
        // if jpg's have already been found, continue writing to current file
        else if (jpgCount > 0)
        {
            fwrite(buffer, sizeof(BYTE), BLOCK, f_out);
        }
    }

    // close open files
    fclose(fp);
    fclose(f_out);

    return 0;
}