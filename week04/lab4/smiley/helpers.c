#include "helpers.h"
#include <stdio.h>

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    // iterate over each of the pixels in the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // variable to hold current pixel for readability
            RGBTRIPLE current = image[i][j];
            if (current.rgbtRed == 0x00 && current.rgbtGreen == 0x00 && current.rgbtBlue == 0x00)
            {
                // set any black pixel to redz
                image[i][j].rgbtRed = 0xFF;
            }
        }
    }
}