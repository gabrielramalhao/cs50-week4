#include "helpers.h"
#include <math.h>
#include <stdio.h>

int higherThan(int value);
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int average = 0;
    int finalAverage = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            average += image[i][j].rgbtRed;
            average += image[i][j].rgbtGreen;
            average += image[i][j].rgbtBlue;

            average = round(average / 3.0);

            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;

            average = 0;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int originalRed = 0;
    int originalGreen = 0;
    int originalBlue = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            originalRed = image[i][j].rgbtRed;
            originalGreen = image[i][j].rgbtGreen;
            originalBlue = image[i][j].rgbtBlue;

            image[i][j].rgbtRed = higherThan(round((0.393 * originalRed) + (0.769 * originalGreen) + (0.189 * originalBlue)));
            image[i][j].rgbtGreen = higherThan(round((0.349 * originalRed) + (0.686 * originalGreen) + (0.168 * originalBlue)));
            image[i][j].rgbtBlue = higherThan(round((0.272 * originalRed) + (0.534 * originalGreen) + (0.131 * originalBlue)));
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int swap = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            swap = image[i][width - (j + 1)].rgbtRed;
            image[i][width - (j + 1)].rgbtRed = image[i][j].rgbtRed;
            image[i][j].rgbtRed = swap;
            swap = 0;

            swap = image[i][width - (j + 1)].rgbtGreen;
            image[i][width - (j + 1)].rgbtGreen = image[i][j].rgbtGreen;
            image[i][j].rgbtGreen = swap;
            swap = 0;

            swap = image[i][width - (j + 1)].rgbtBlue;
            image[i][width - (j + 1)].rgbtBlue = image[i][j].rgbtBlue;
            image[i][j].rgbtBlue = swap;
            swap = 0;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float tempRed = 0, tempGreen = 0, tempBlue = 0, pixelCount = 0;
            for (int local_i = i - 1; local_i <= i + 1; local_i++)
            {
                for (int local_j = j - 1; local_j <= j + 1; local_j++)
                {
                    if (local_i >= 0 && local_i < height && local_j >= 0 && local_j < width)
                    {
                        tempRed += image[local_i][local_j].rgbtRed;
                        tempGreen += image[local_i][local_j].rgbtGreen;
                        tempBlue += image[local_i][local_j].rgbtBlue;

                        pixelCount++;
                    }
                }
            }
            copy[i][j].rgbtRed = round(tempRed / pixelCount);
            copy[i][j].rgbtGreen = round(tempGreen / pixelCount);
            copy[i][j].rgbtBlue = round(tempBlue / pixelCount);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = copy[i][j];
        }
    }
}

int higherThan(int value)
{
    if (value > 255)
    {
        return 255;
    }
    return value;
}