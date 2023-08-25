#include "helpers.h"
#include <stdio.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // for loop to iterate through the rows
    for (int i = 0; i < height; i++)
    {
        // for loop to iterate over each pixel
        for (int j = 0; j < width; j++)
        {
            // calc mean
            int average = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);

            // set mean value to each colour in pixel
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // for loop to iterate through the rows
    for (int i = 0; i < height; i++)
    {
        // for loop to iterate over each pixel
        for (int j = 0; j < width; j++)
        {
            // calc sepiaRed
            float sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }

            // calc sepiaGreen
            float sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }

            // sepiaBlue
            float sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            // set sepia value to each colour in pixel
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // calc how many swaps need to be made
    int swaps = (int)round(width / 2.0);

    // iterate over rows
    for (int i = 0; i < height; i++)
    {
        // iterate over columns
        for (int j = 0; j < swaps; j++)
        {
            // temp variable to hold current pixel
            RGBTRIPLE temp = image[i][j];

            // swap current pixel with it's mirrored pixel in array
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // temp buffer to hold blurred values
    RGBTRIPLE buffer[height][width];

    // variables to hold the values for edges
    int lastRow = height - 1;
    int lastColumn = width - 1;


    // iterate through each row
    for (int h = 0; h < height; h++)
    {
        // iterate through each pixel in row
        for (int w = 0; w < width; w++)
        {
            // variables to hold total values for average calc. set to 0 for each pixel
            int totalRed = 0;
            int totalGreen = 0;
            int totalBlue = 0;

            // current pixel and it's information added to total
            totalRed += image[h][w].rgbtRed;
            totalGreen += image[h][w].rgbtGreen;
            totalBlue += image[h][w].rgbtBlue;

            // variable to track how many pixels we are using to get average
            float pixelCount = 1.0;

            // left
            if (w > 0)
            {
                totalRed += image[h][w - 1].rgbtRed;
                totalGreen += image[h][w - 1].rgbtGreen;
                totalBlue += image[h][w - 1].rgbtBlue;
                pixelCount += 1;
            }

            // right
            if (w < lastColumn)
            {
                totalRed += image[h][w + 1].rgbtRed;
                totalGreen += image[h][w + 1].rgbtGreen;
                totalBlue += image[h][w + 1].rgbtBlue;
                pixelCount += 1;
            }

            // above
            if (h > 0)
            {
                totalRed += image[h - 1][w].rgbtRed;
                totalGreen += image[h - 1][w].rgbtGreen;
                totalBlue += image[h - 1][w].rgbtBlue;
                pixelCount += 1;

                // topLeft
                if (h > 0 && w > 0)
                {
                    totalRed += image[h - 1][w - 1].rgbtRed;
                    totalGreen += image[h - 1][w - 1].rgbtGreen;
                    totalBlue += image[h - 1][w - 1].rgbtBlue;
                    pixelCount += 1;
                }
                // topRight
                if (h > 0 && w < lastColumn)
                {
                    totalRed += image[h - 1][w + 1].rgbtRed;
                    totalGreen += image[h - 1][w + 1].rgbtGreen;
                    totalBlue += image[h - 1][w + 1].rgbtBlue;
                    pixelCount += 1;
                }
            }

            // below
            if (h < lastRow)
            {
                totalRed += image[h + 1][w].rgbtRed;
                totalGreen += image[h + 1][w].rgbtGreen;
                totalBlue += image[h + 1][w].rgbtBlue;
                pixelCount += 1;

                // bottomLeft
                if (h < lastRow && w > 0)
                {
                    totalRed += image[h + 1][w - 1].rgbtRed;
                    totalGreen += image[h + 1][w - 1].rgbtGreen;
                    totalBlue += image[h + 1][w - 1].rgbtBlue;
                    pixelCount += 1;
                }
                // bottomRight
                if (h < lastRow && w < lastColumn)
                {
                    totalRed += image[h + 1][w + 1].rgbtRed;
                    totalGreen += image[h + 1][w + 1].rgbtGreen;
                    totalBlue += image[h + 1][w + 1].rgbtBlue;
                    pixelCount += 1;
                }
            }

            // fill buffer array with the rgb values for each pixel
            buffer[h][w].rgbtRed = round(totalRed / pixelCount);
            buffer[h][w].rgbtGreen = round(totalGreen / pixelCount);
            buffer[h][w].rgbtBlue = round(totalBlue / pixelCount);
        }
    }

    // iterate over the original and change the values to buffer values
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = buffer[i][j];
        }
    }
    return;
}
