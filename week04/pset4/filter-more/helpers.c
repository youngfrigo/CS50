#include "helpers.h"
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


// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // buffer to hold pixel values
    RGBTRIPLE buffer[height][width];
    RGBTRIPLE current;
    RGBTRIPLE top;
    RGBTRIPLE bottom;
    RGBTRIPLE left;
    RGBTRIPLE right;
    RGBTRIPLE topLeft;
    RGBTRIPLE topRight;
    RGBTRIPLE bottomLeft;
    RGBTRIPLE bottomRight;

    // iterate over each row
    for (int h = 0; h < height; h++)
    {
        // iterate over each pixel in row
        for (int w = 0; w < width; w++)
        {
            // variables to hold Gx and Gy values for each colour
            int GxRed = 0;
            int GyRed = 0;
            int GxGreen = 0;
            int GyGreen = 0;
            int GxBlue = 0;
            int GyBlue = 0;

            // variables to hold squared Gx and Gy, and square root of the sum of GxRed^2 and GyRed^2
            int GxRedSquared = 0;
            int GyRedSquared = 0;
            int redSqRoot = 0;

            // variables to hold squared Gx and Gy, and square root of the sum of GxGreen^2 and GyGreen^2
            int GxGreenSquared = 0;
            int GyGreenSquared = 0;
            int greenSqRoot = 0;

            // variables to hold squared Gx and Gy, and square root of the sum of GxBlue^2 and GyBlue^2
            int GxBlueSquared = 0;
            int GyBlueSquared = 0;
            int blueSqRoot = 0;

            current = image[h][w];

            // top
            if (h > 0)
            {
                top = image[h - 1][w];
            }
            else
            {
                top.rgbtRed = 0;
                top.rgbtGreen = 0;
                top.rgbtBlue = 0;
            }

            // bottom
            if (h < height - 1)
            {
                bottom = image[h + 1][w];
            }
            else
            {
                bottom.rgbtRed = 0;
                bottom.rgbtGreen = 0;
                bottom.rgbtBlue = 0;
            }

            // left
            if (w > 0)
            {
                left = image[h][w - 1];
            }
            else
            {
                left.rgbtRed = 0;
                left.rgbtGreen = 0;
                left.rgbtBlue = 0;
            }

            // right
            if (w < width - 1)
            {
                right = image[h][w + 1];
            }
            else
            {
                right.rgbtRed = 0;
                right.rgbtGreen = 0;
                right.rgbtBlue = 0;
            }

            // topLeft
            if (h > 0 && w > 0)
            {
                topLeft = image[h - 1][w - 1];
            }
            else
            {
                topLeft.rgbtRed = 0;
                topLeft.rgbtGreen = 0;
                topLeft.rgbtBlue = 0;
            }

            // topRight
            if (h > 0 && w < width - 1)
            {
                topRight = image[h - 1][w + 1];
            }
            else
            {
                topRight.rgbtRed = 0;
                topRight.rgbtGreen = 0;
                topRight.rgbtBlue = 0;
            }

            // bottomLeft
            if (h < height - 1 && w > 0)
            {
                bottomLeft = image[h + 1][w - 1];
            }
            else
            {
                bottomLeft.rgbtRed = 0;
                bottomLeft.rgbtGreen = 0;
                bottomLeft.rgbtBlue = 0;
            }

            // bottomRight
            if (h < height - 1 && w < width - 1)
            {
                bottomRight = image[h + 1][w + 1];
            }
            else
            {
                bottomRight.rgbtRed = 0;
                bottomRight.rgbtGreen = 0;
                bottomRight.rgbtBlue = 0;
            }


            // perform Gx and Gy calculations for the red value of current pixel
            GxRed = (topLeft.rgbtRed * -1) + (top.rgbtRed * 0) + (topRight.rgbtRed * 1) + (left.rgbtRed * -2) +
                    (current.rgbtRed * 0) + (right.rgbtRed * 2) + (bottomLeft.rgbtRed * -1) + (bottom.rgbtRed * 0) +
                    (bottomRight.rgbtRed * 1);
            GyRed = (topLeft.rgbtRed * -1) + (top.rgbtRed * -2) + (topRight.rgbtRed * -1) + (left.rgbtRed * 0) +
                    (current.rgbtRed * 0) + (right.rgbtRed * 0) + (bottomLeft.rgbtRed * 1) + (bottom.rgbtRed * 2) +
                    (bottomRight.rgbtRed * 1);

            // perform Gx and Gy calculations for the green value of current pixel
            GxGreen = (topLeft.rgbtGreen * -1) + (top.rgbtGreen * 0) + (topRight.rgbtGreen * 1) + (left.rgbtGreen * -2) +
                      (current.rgbtGreen * 0) + (right.rgbtGreen * 2) + (bottomLeft.rgbtGreen * -1) + (bottom.rgbtGreen * 0) +
                      (bottomRight.rgbtGreen * 1);
            GyGreen = (topLeft.rgbtGreen * -1) + (top.rgbtGreen * -2) + (topRight.rgbtGreen * -1) + (left.rgbtGreen * 0) +
                      (current.rgbtGreen * 0) + (right.rgbtGreen * 0) + (bottomLeft.rgbtGreen * 1) + (bottom.rgbtGreen * 2) +
                      (bottomRight.rgbtGreen * 1);

            // perform Gx and Gy calculations for the blue value of current pixel
            GxBlue = (topLeft.rgbtBlue * -1) + (top.rgbtBlue * 0) + (topRight.rgbtBlue * 1) + (left.rgbtBlue * -2) +
                     (current.rgbtBlue * 0) + (right.rgbtBlue * 2) + (bottomLeft.rgbtBlue * -1) + (bottom.rgbtBlue * 0) +
                     (bottomRight.rgbtBlue * 1);
            GyBlue = (topLeft.rgbtBlue * -1) + (top.rgbtBlue * -2) + (topRight.rgbtBlue * -1) + (left.rgbtBlue * 0) +
                     (current.rgbtBlue * 0) + (right.rgbtBlue * 0) + (bottomLeft.rgbtBlue * 1) + (bottom.rgbtBlue * 2) +
                     (bottomRight.rgbtBlue * 1);

            // after square rooting assign new value of red, if greater than 255, set to 255(MAX)
            GxRedSquared = GxRed * GxRed;
            GyRedSquared = GyRed * GyRed;
            redSqRoot = (int)round(sqrt(GxRedSquared + GyRedSquared));
            buffer[h][w].rgbtRed = redSqRoot;
            if (redSqRoot > 255)
            {
                buffer[h][w].rgbtRed = 255;
            }

            // after square rooting assign new value of green, if greater than 255, set to 255(MAX)
            GxGreenSquared = GxGreen * GxGreen;
            GyGreenSquared = GyGreen * GyGreen;
            greenSqRoot = (int)round(sqrt(GxGreenSquared + GyGreenSquared));
            buffer[h][w].rgbtGreen = greenSqRoot;
            if (greenSqRoot > 255)
            {
                buffer[h][w].rgbtGreen = 255;
            }

            // after square rooting assign new value of blue, if greater than 255, set to 255(MAX)
            GxBlueSquared = GxBlue * GxBlue;
            GyBlueSquared = GyBlue * GyBlue;
            blueSqRoot = (int)round(sqrt(GxBlueSquared + GyBlueSquared));
            buffer[h][w].rgbtBlue = blueSqRoot;
            if (blueSqRoot > 255)
            {
                buffer[h][w].rgbtBlue = 255;
            }
        }
    }

    // final loop to set the new values to the original image
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            image[h][w] = buffer[h][w];
        }
    }
    return;
}