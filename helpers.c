#include "helpers.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculates the average of the three rgb channels for each pixel.
            float n = (image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen) / 3.0;
            int rn = round(n);
            // Assign the new values of the rgb channel for each pixel.
            image[i][j].rgbtGreen = rn;
            image[i][j].rgbtBlue = rn;
            image[i][j].rgbtRed = rn;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE n;
    int w = width - 1; // Stores the value of the last pixel in row.
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // loops through the row and swaps the last index with first index.
            n = image[i][j];
            image[i][j] = image[i][w - j];
            image[i][w - j] = n;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE img[height][width];
    int h = height - 1;
    int w = width - 1;

    float red;
    float blue;
    float green;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            img[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Blurs the middle pixels.
            if (i + 1 <= h && j + 1 <= w && i - 1 != - 1 && j - 1 != - 1)
            {
                red = (img[i - 1][j - 1].rgbtRed + img[i - 1][j].rgbtRed + img[i - 1][j + 1].rgbtRed + img[i][j + 1].rgbtRed +
                       img[i + 1][j + 1].rgbtRed + img[i + 1][j].rgbtRed + img[i + 1][j - 1].rgbtRed +
                       img[i][j - 1].rgbtRed + img[i][j].rgbtRed) / 9.0;
                blue = (img[i - 1][j - 1].rgbtBlue + img[i - 1][j].rgbtBlue + img[i - 1][j + 1].rgbtBlue + img[i][j + 1].rgbtBlue +
                        img[i + 1][j + 1].rgbtBlue + img[i + 1][j].rgbtBlue + img[i + 1][j - 1].rgbtBlue +
                        img[i][j - 1].rgbtBlue + img[i][j].rgbtBlue) / 9.0;
                green = (img[i - 1][j - 1].rgbtGreen + img[i - 1][j].rgbtGreen + img[i - 1][j + 1].rgbtGreen + img[i][j + 1].rgbtGreen +
                         img[i + 1][j + 1].rgbtGreen + img[i + 1][j].rgbtGreen + img[i + 1][j - 1].rgbtGreen +
                         img[i][j - 1].rgbtGreen + img[i][j].rgbtGreen) / 9.0;
            }

            // Blurs the edge pixels.
            if (i - 1 == - 1 && j - 1 > - 1)
            {
                red = (img[i][j - 1].rgbtRed + img[i + 1][j - 1].rgbtRed + img[i + 1][j].rgbtRed + img[i + 1][j + 1].rgbtRed +
                       img[i][j + 1].rgbtRed + img[i][j].rgbtRed) / 6.0;
                blue = (img[i][j - 1].rgbtBlue + img[i + 1][j - 1].rgbtBlue + img[i + 1][j].rgbtBlue + img[i + 1][j + 1].rgbtBlue +
                        img[i][j + 1].rgbtBlue + img[i][j].rgbtBlue) / 6.0;
                green = (img[i][j - 1].rgbtGreen + img[i + 1][j - 1].rgbtGreen + img[i + 1][j].rgbtGreen + img[i + 1][j + 1].rgbtGreen +
                         img[i][j + 1].rgbtGreen + img[i][j].rgbtGreen) / 6.0;
            }
            else if (j - 1 == - 1 && i - 1 > - 1)
            {
                red = (img[i - 1][j].rgbtRed + img[i - 1][j + 1].rgbtRed + img[i][j + 1].rgbtRed + img[i + 1][j + 1].rgbtRed +
                       img[i + 1][j].rgbtRed + img[i][j].rgbtRed) / 6.0;
                blue = (img[i - 1][j].rgbtBlue + img[i - 1][j + 1].rgbtBlue + img[i][j + 1].rgbtBlue + img[i + 1][j + 1].rgbtBlue +
                        img[i + 1][j].rgbtBlue + img[i][j].rgbtBlue) / 6.0;
                green = (img[i - 1][j].rgbtGreen + img[i - 1][j + 1].rgbtGreen + img[i][j + 1].rgbtGreen + img[i + 1][j + 1].rgbtGreen +
                         img[i + 1][j].rgbtGreen + img[i][j].rgbtGreen) / 6.0;
            }
            else if (j + 1 > w && i - 1 > - 1)
            {
                red = (img[i - 1][j].rgbtRed + img[i - 1][j - 1].rgbtRed + img[i][j - 1].rgbtRed + img[i + 1][j - 1].rgbtRed +
                       img[i + 1][j].rgbtRed + img[i][j].rgbtRed) / 6.0;
                blue = (img[i - 1][j].rgbtBlue + img[i - 1][j - 1].rgbtBlue + img[i][j - 1].rgbtBlue + img[i + 1][j - 1].rgbtBlue +
                        img[i + 1][j].rgbtBlue + img[i][j].rgbtBlue) / 6.0;
                green = (img[i - 1][j].rgbtGreen + img[i - 1][j - 1].rgbtGreen + img[i][j - 1].rgbtGreen + img[i + 1][j - 1].rgbtGreen +
                         img[i + 1][j].rgbtGreen + img[i][j].rgbtGreen) / 6.0;
            }
            else if (i + 1 > h && j - 1 > - 1)
            {
                red = (img[i][j - 1].rgbtRed + img[i - 1][j - 1].rgbtRed + img[i - 1][j].rgbtRed + img[i - 1][j + 1].rgbtRed +
                       img[i][j + 1].rgbtRed + img[i][j].rgbtRed) / 6.0;
                blue = (img[i][j - 1].rgbtBlue + img[i - 1][j - 1].rgbtBlue + img[i - 1][j].rgbtBlue + img[i - 1][j + 1].rgbtBlue +
                        img[i][j + 1].rgbtBlue + img[i][j].rgbtBlue) / 6.0;
                green = (img[i][j - 1].rgbtGreen + img[i - 1][j - 1].rgbtGreen + img[i - 1][j].rgbtGreen + img[i - 1][j + 1].rgbtGreen +
                         img[i][j + 1].rgbtGreen + img[i][j].rgbtGreen) / 6.0;
            }

            // Blurs the corner pixels
            if (j + 1 > w && i + 1 > h)
            {
                red = (img[i][j - 1].rgbtRed + img[i - 1][j - 1].rgbtRed + img[i - 1][j].rgbtRed + img[i][j].rgbtRed) / 4.0;
                blue = (img[i][j - 1].rgbtBlue + img[i - 1][j - 1].rgbtBlue + img[i - 1][j].rgbtBlue + img[i][j].rgbtBlue) / 4.0;
                green = (img[i][j - 1].rgbtGreen + img[i - 1][j - 1].rgbtGreen + img[i - 1][j].rgbtGreen + img[i][j].rgbtGreen) / 4.0;
            }
            else if (i + 1 > h && j - 1 == -1)
            {
                red = (img[i - 1][j].rgbtRed + img[i - 1][j + 1].rgbtRed + img[i][j + 1].rgbtRed + img[i][j].rgbtRed) / 4.0;
                blue = (img[i - 1][j].rgbtBlue + img[i - 1][j + 1].rgbtBlue + img[i][j + 1].rgbtBlue + img[i][j].rgbtBlue) / 4.0;
                green = (img[i - 1][j].rgbtGreen + img[i - 1][j + 1].rgbtGreen + img[i][j + 1].rgbtGreen + img[i][j].rgbtGreen) / 4.0;
            }
            else if (i - 1 == -1 && j - 1 == -1)
            {
                red = (img[i][j + 1].rgbtRed + img[i + 1][j + 1].rgbtRed + img[i + 1][j].rgbtRed + img[i][j].rgbtRed) / 4.0;
                blue = (img[i][j + 1].rgbtBlue + img[i + 1][j + 1].rgbtBlue + img[i + 1][j].rgbtBlue + img[i][j].rgbtBlue) / 4.0;
                green = (img[i][j + 1].rgbtGreen + img[i + 1][j + 1].rgbtGreen + img[i + 1][j].rgbtGreen + img[i][j].rgbtGreen) / 4.0;
            }
            else if (j + 1 > h && i - 1 == - 1)
            {
                red = (img[i][j - 1].rgbtRed + img[i + 1][j - 1].rgbtRed + img[i + 1][j].rgbtRed + img[i][j].rgbtRed) / 4.0;
                blue = (img[i][j - 1].rgbtBlue + img[i + 1][j - 1].rgbtBlue + img[i + 1][j].rgbtBlue + img[i][j].rgbtBlue) / 4.0;
                green = (img[i][j - 1].rgbtGreen + img[i + 1][j - 1].rgbtGreen + img[i + 1][j].rgbtGreen + img[i][j].rgbtGreen) / 4.0;
            }

            int ngreen = round(green);
            int nblue = round(blue);
            int nred = round(red);

            //stores the new values of the rgb channel
            image[i][j].rgbtGreen = ngreen;
            image[i][j].rgbtBlue = nblue;
            image[i][j].rgbtRed = nred;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE img[height][width];
    int h = height - 1;
    int w = width - 1;

    //
    int redGx;
    int blueGx;
    int greenGx;
    //
    int redGy;
    int blueGy;
    int greenGy;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            img[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Detects the edge of the middle pixels.
            if (i + 1 <= h && j + 1 <= w && i - 1 != - 1 && j - 1 != - 1)
            {
                //
                redGx = ((img[i - 1][j - 1].rgbtRed * - 1) + (img[i - 1][j].rgbtRed * 0) + (img[i - 1][j + 1].rgbtRed * 1) +
                         (img[i][j + 1].rgbtRed * 2) + (img[i + 1][j + 1].rgbtRed * 1) + (img[i + 1][j].rgbtRed * 0) +
                         (img[i + 1][j - 1].rgbtRed * - 1) + (img[i][j - 1].rgbtRed * - 2) + (img[i][j].rgbtRed * 0));
                blueGx = ((img[i - 1][j - 1].rgbtBlue * - 1) + (img[i - 1][j].rgbtBlue * 0) + (img[i - 1][j + 1].rgbtBlue * 1) +
                          (img[i][j + 1].rgbtBlue * 2) + (img[i + 1][j + 1].rgbtBlue * 1) + (img[i + 1][j].rgbtBlue * 0) +
                          (img[i + 1][j - 1].rgbtBlue * - 1) + (img[i][j - 1].rgbtBlue * - 2) + (img[i][j].rgbtBlue * 0));
                greenGx = ((img[i - 1][j - 1].rgbtGreen * - 1) + (img[i - 1][j].rgbtGreen * 0) + (img[i - 1][j + 1].rgbtGreen * 1) +
                           (img[i][j + 1].rgbtGreen * 2) + (img[i + 1][j + 1].rgbtGreen * 1) + (img[i + 1][j].rgbtGreen * 0) +
                           (img[i + 1][j - 1].rgbtGreen * - 1) + (img[i][j - 1].rgbtGreen * - 2) + (img[i][j].rgbtGreen * 0));
                //
                redGy = ((img[i - 1][j - 1].rgbtRed * - 1) + (img[i - 1][j].rgbtRed * - 2) + (img[i - 1][j + 1].rgbtRed * - 1) +
                         (img[i][j + 1].rgbtRed * 0) + (img[i + 1][j + 1].rgbtRed * 1) + (img[i + 1][j].rgbtRed * 2) +
                         (img[i + 1][j - 1].rgbtRed * 1) + (img[i][j - 1].rgbtRed * 0) + (img[i][j].rgbtRed * 0));
                blueGy = ((img[i - 1][j - 1].rgbtBlue * - 1) + (img[i - 1][j].rgbtBlue * - 2) + (img[i - 1][j + 1].rgbtBlue * - 1) +
                          (img[i][j + 1].rgbtBlue * 0) + (img[i + 1][j + 1].rgbtBlue * 1) + (img[i + 1][j].rgbtBlue * 2) +
                          (img[i + 1][j - 1].rgbtBlue * 1) + (img[i][j - 1].rgbtBlue * 0) + (img[i][j].rgbtBlue * 0));
                greenGy = ((img[i - 1][j - 1].rgbtGreen * - 1) + (img[i - 1][j].rgbtGreen * - 2) + (img[i - 1][j + 1].rgbtGreen * - 1) +
                           (img[i][j + 1].rgbtGreen * 0) + (img[i + 1][j + 1].rgbtGreen * 1) + (img[i + 1][j].rgbtGreen * 2) +
                           (img[i + 1][j - 1].rgbtGreen * 1) + (img[i][j - 1].rgbtGreen * 0) + (img[i][j].rgbtGreen * 0));
            }

            // Detects the edge of the edge pixels.
            if (i - 1 == - 1 && j - 1 > - 1)
            {
                //
                redGx = ((img[i][j - 1].rgbtRed * - 2) + (img[i + 1][j - 1].rgbtRed * - 1) + (img[i + 1][j].rgbtRed * 0) +
                         (img[i + 1][j + 1].rgbtRed * 1) + (img[i][j + 1].rgbtRed * 2) + (img[i][j].rgbtRed * 0));
                blueGx = ((img[i][j - 1].rgbtBlue * - 2) + (img[i + 1][j - 1].rgbtBlue * - 1) + (img[i + 1][j].rgbtBlue * 0) +
                          (img[i + 1][j + 1].rgbtBlue * 1) + (img[i][j + 1].rgbtBlue * 2) + (img[i][j].rgbtBlue * 0));
                greenGx = ((img[i][j - 1].rgbtGreen * - 2) + (img[i + 1][j - 1].rgbtGreen * - 1) + (img[i + 1][j].rgbtGreen * 0) +
                           (img[i + 1][j + 1].rgbtGreen * 1) + (img[i][j + 1].rgbtGreen * 2) + (img[i][j].rgbtGreen * 0));
                //
                redGy = ((img[i][j - 1].rgbtRed * 0) + (img[i + 1][j - 1].rgbtRed * 1) + (img[i + 1][j].rgbtRed * 2) +
                         (img[i + 1][j + 1].rgbtRed * 1) + (img[i][j + 1].rgbtRed * 0) + (img[i][j].rgbtRed * 0));
                blueGy = ((img[i][j - 1].rgbtBlue * 0) + (img[i + 1][j - 1].rgbtBlue * 1) + (img[i + 1][j].rgbtBlue * 2) +
                          (img[i + 1][j + 1].rgbtBlue * 1) + (img[i][j + 1].rgbtBlue * 0) + (img[i][j].rgbtBlue * 0));
                greenGy = ((img[i][j - 1].rgbtGreen * 0) + (img[i + 1][j - 1].rgbtGreen * 1) + (img[i + 1][j].rgbtGreen * 2) +
                           (img[i + 1][j + 1].rgbtGreen * 1) + (img[i][j + 1].rgbtGreen * 0) + (img[i][j].rgbtGreen * 0));
            }
            else if (j - 1 == - 1 && i - 1 > - 1)
            {
                //
                redGx = ((img[i - 1][j].rgbtRed * 0) + (img[i - 1][j + 1].rgbtRed * 1) + (img[i][j + 1].rgbtRed * 2) +
                         (img[i + 1][j + 1].rgbtRed * 1) + (img[i + 1][j].rgbtRed * 0) + (img[i][j].rgbtRed * 0));
                blueGx = ((img[i - 1][j].rgbtBlue * 0) + (img[i - 1][j + 1].rgbtBlue * 1) + (img[i][j + 1].rgbtBlue * 2) +
                          (img[i + 1][j + 1].rgbtBlue * 1) + (img[i + 1][j].rgbtBlue * 0) + (img[i][j].rgbtBlue * 0));
                greenGx = ((img[i - 1][j].rgbtGreen * 0) + (img[i - 1][j + 1].rgbtGreen * 1) + (img[i][j + 1].rgbtGreen * 2) +
                           (img[i + 1][j + 1].rgbtGreen * 1) + (img[i + 1][j].rgbtGreen * 0) + (img[i][j].rgbtGreen * 0));
                //
                redGy = ((img[i - 1][j].rgbtRed * - 2) + (img[i - 1][j + 1].rgbtRed * - 1) + (img[i][j + 1].rgbtRed * 0) +
                         (img[i + 1][j + 1].rgbtRed * 1) + (img[i + 1][j].rgbtRed * 2) + (img[i][j].rgbtRed * 0));
                blueGy = ((img[i - 1][j].rgbtBlue * - 2) + (img[i - 1][j + 1].rgbtBlue * - 1) + (img[i][j + 1].rgbtBlue * 0) +
                          (img[i + 1][j + 1].rgbtBlue * 1) + (img[i + 1][j].rgbtBlue * 2) + (img[i][j].rgbtBlue * 0));
                greenGy = ((img[i - 1][j].rgbtGreen * - 2) + (img[i - 1][j + 1].rgbtGreen * - 1) + (img[i][j + 1].rgbtGreen * 0) +
                           (img[i + 1][j + 1].rgbtGreen * 1) + (img[i + 1][j].rgbtGreen * 2) + (img[i][j].rgbtGreen * 0));
            }
            else if (j + 1 > w && i - 1 > - 1)
            {
                //
                redGx = ((img[i - 1][j].rgbtRed * 0) + (img[i - 1][j - 1].rgbtRed * - 1) + (img[i][j - 1].rgbtRed * - 2) +
                         (img[i + 1][j - 1].rgbtRed * - 1) + (img[i + 1][j].rgbtRed * 0) + (img[i][j].rgbtRed * 0));
                blueGx = ((img[i - 1][j].rgbtBlue * 0) + (img[i - 1][j - 1].rgbtBlue * - 1) + (img[i][j - 1].rgbtBlue * - 2) +
                          (img[i + 1][j - 1].rgbtBlue * - 1) + (img[i + 1][j].rgbtBlue * 0) + (img[i][j].rgbtBlue * 0));
                greenGx = ((img[i - 1][j].rgbtGreen * 0) + (img[i - 1][j - 1].rgbtGreen * - 1) + (img[i][j - 1].rgbtGreen * - 2) +
                           (img[i + 1][j - 1].rgbtGreen * - 1) + (img[i + 1][j].rgbtGreen * 0) + (img[i][j].rgbtGreen * 0));
                //
                redGy = ((img[i - 1][j].rgbtRed * - 2) + (img[i - 1][j - 1].rgbtRed * - 1) + (img[i][j - 1].rgbtRed * 0) +
                         (img[i + 1][j - 1].rgbtRed * 1) + (img[i + 1][j].rgbtRed * 2) + (img[i][j].rgbtRed * 0));
                blueGy = ((img[i - 1][j].rgbtBlue * - 2) + (img[i - 1][j - 1].rgbtBlue * - 1) + (img[i][j - 1].rgbtBlue * 0) +
                          (img[i + 1][j - 1].rgbtBlue * 1) + (img[i + 1][j].rgbtBlue * 2) + (img[i][j].rgbtBlue * 0));
                greenGy = ((img[i - 1][j].rgbtGreen * - 2) + (img[i - 1][j - 1].rgbtGreen * - 1) + (img[i][j - 1].rgbtGreen * 0) +
                           (img[i + 1][j - 1].rgbtGreen * 1) + (img[i + 1][j].rgbtGreen * 2) + (img[i][j].rgbtGreen * 0));
            }
            else if (i + 1 > h && j - 1 > - 1)
            {
                //
                redGx = ((img[i][j - 1].rgbtRed * - 2) + (img[i - 1][j - 1].rgbtRed * - 1) + (img[i - 1][j].rgbtRed * 0) +
                         (img[i - 1][j + 1].rgbtRed * 1) + (img[i][j + 1].rgbtRed * 2) + (img[i][j].rgbtRed * 0));
                blueGx = ((img[i][j - 1].rgbtBlue * - 2) + (img[i - 1][j - 1].rgbtBlue * - 1) + (img[i - 1][j].rgbtBlue * 0) +
                          (img[i - 1][j + 1].rgbtBlue * 1) + (img[i][j + 1].rgbtBlue * 2) + (img[i][j].rgbtBlue * 0));
                greenGx = ((img[i][j - 1].rgbtGreen * - 2) + (img[i - 1][j - 1].rgbtGreen * - 1) + (img[i - 1][j].rgbtGreen * 0) +
                           (img[i - 1][j + 1].rgbtGreen * 1) + (img[i][j + 1].rgbtGreen * 2) + (img[i][j].rgbtGreen * 0));
                //
                redGy = ((img[i][j - 1].rgbtRed * 0) + (img[i - 1][j - 1].rgbtRed * - 1) + (img[i - 1][j].rgbtRed * - 2) +
                         (img[i - 1][j + 1].rgbtRed * - 1) + (img[i][j + 1].rgbtRed * 0) + (img[i][j].rgbtRed * 0));
                blueGy = ((img[i][j - 1].rgbtBlue * 0) + (img[i - 1][j - 1].rgbtBlue * - 1) + (img[i - 1][j].rgbtBlue * - 2) +
                          (img[i - 1][j + 1].rgbtBlue * - 1) + (img[i][j + 1].rgbtBlue * 0) + (img[i][j].rgbtBlue * 0));
                greenGy = ((img[i][j - 1].rgbtGreen * 0) + (img[i - 1][j - 1].rgbtGreen * - 1) + (img[i - 1][j].rgbtGreen * - 2) +
                           (img[i - 1][j + 1].rgbtGreen * - 1) + (img[i][j + 1].rgbtGreen * 0) + (img[i][j].rgbtGreen * 0));
            }

            // Detects the edge of the the corner pixels
            if (j + 1 > w && i + 1 > h)
            {
                //
                redGx = ((img[i][j - 1].rgbtRed * - 2) + (img[i - 1][j - 1].rgbtRed * - 1) + (img[i - 1][j].rgbtRed * 0) + (img[i][j].rgbtRed * 0));
                blueGx = ((img[i][j - 1].rgbtBlue * - 2) + (img[i - 1][j - 1].rgbtBlue * - 1) + (img[i - 1][j].rgbtBlue * 0) +
                          (img[i][j].rgbtBlue * 0));
                greenGx = ((img[i][j - 1].rgbtGreen * - 2) + (img[i - 1][j - 1].rgbtGreen * - 1) + (img[i - 1][j].rgbtGreen * 0) +
                           (img[i][j].rgbtGreen * 0));
                //
                redGy = ((img[i][j - 1].rgbtRed * 0) + (img[i - 1][j - 1].rgbtRed * - 1) + (img[i - 1][j].rgbtRed * - 2) + (img[i][j].rgbtRed * 0));
                blueGy = ((img[i][j - 1].rgbtBlue * 0) + (img[i - 1][j - 1].rgbtBlue * - 1) + (img[i - 1][j].rgbtBlue * - 2) +
                          (img[i][j].rgbtBlue * 0));
                greenGy = ((img[i][j - 1].rgbtGreen * 0) + (img[i - 1][j - 1].rgbtGreen * - 1) + (img[i - 1][j].rgbtGreen * - 2) +
                           (img[i][j].rgbtGreen * 0));
            }
            else if (i + 1 > h && j - 1 == -1)
            {
                //
                redGx = ((img[i - 1][j].rgbtRed * 0) + (img[i - 1][j + 1].rgbtRed * 1) + (img[i][j + 1].rgbtRed * 2) + (img[i][j].rgbtRed * 0));
                blueGx = ((img[i - 1][j].rgbtBlue * 0) + (img[i - 1][j + 1].rgbtBlue * 1) + (img[i][j + 1].rgbtBlue * 2) +
                          (img[i][j].rgbtBlue * 0));
                greenGx = ((img[i - 1][j].rgbtGreen * 0) + (img[i - 1][j + 1].rgbtGreen * 1) + (img[i][j + 1].rgbtGreen * 2) +
                           (img[i][j].rgbtGreen * 0));
                //
                redGy = ((img[i - 1][j].rgbtRed * - 2) + (img[i - 1][j + 1].rgbtRed * - 1) + (img[i][j + 1].rgbtRed * 0) +
                         (img[i][j].rgbtRed * 0));
                blueGy = ((img[i - 1][j].rgbtBlue * - 2) + (img[i - 1][j + 1].rgbtBlue * - 1) + (img[i][j + 1].rgbtBlue * 0) +
                          (img[i][j].rgbtBlue * 0));
                greenGy = ((img[i - 1][j].rgbtGreen * - 2) + (img[i - 1][j + 1].rgbtGreen * - 1) + (img[i][j + 1].rgbtGreen * 0) +
                           (img[i][j].rgbtGreen * 0));
            }
            else if (i - 1 == -1 && j - 1 == -1)
            {
                //
                redGx = ((img[i][j + 1].rgbtRed * 2) + (img[i + 1][j + 1].rgbtRed * 1) + (img[i + 1][j].rgbtRed * 0) + (img[i][j].rgbtRed * 0));
                blueGx = ((img[i][j + 1].rgbtBlue * 2) + (img[i + 1][j + 1].rgbtBlue * 1) + (img[i + 1][j].rgbtBlue * 0) +
                          (img[i][j].rgbtBlue * 0));
                greenGx = ((img[i][j + 1].rgbtGreen * 2) + (img[i + 1][j + 1].rgbtGreen * 1) + (img[i + 1][j].rgbtGreen * 0) +
                           (img[i][j].rgbtGreen * 0));
                //
                redGy = ((img[i][j + 1].rgbtRed * 0) + (img[i + 1][j + 1].rgbtRed * 1) + (img[i + 1][j].rgbtRed * 2) + (img[i][j].rgbtRed * 0));
                blueGy = ((img[i][j + 1].rgbtBlue * 0) + (img[i + 1][j + 1].rgbtBlue * 1) + (img[i + 1][j].rgbtBlue * 2) +
                          (img[i][j].rgbtBlue * 0));
                greenGy = ((img[i][j + 1].rgbtGreen * 0) + (img[i + 1][j + 1].rgbtGreen * 1) + (img[i + 1][j].rgbtGreen * 2) +
                           (img[i][j].rgbtGreen * 0));
            }
            else if (j + 1 > h && i - 1 == - 1)
            {
                //
                redGx = ((img[i][j - 1].rgbtRed * - 2) + (img[i + 1][j - 1].rgbtRed * - 1) + (img[i + 1][j].rgbtRed * 0) + (img[i][j].rgbtRed * 0));
                blueGx = ((img[i][j - 1].rgbtBlue * - 2) + (img[i + 1][j - 1].rgbtBlue * - 1) + (img[i + 1][j].rgbtBlue * 0) +
                          (img[i][j].rgbtBlue * 0));
                greenGx = ((img[i][j - 1].rgbtGreen * - 2) + (img[i + 1][j - 1].rgbtGreen * - 1) + (img[i + 1][j].rgbtGreen * 0) +
                           (img[i][j].rgbtGreen * 0));
                //
                redGy = ((img[i][j - 1].rgbtRed * 0) + (img[i + 1][j - 1].rgbtRed * 1) + (img[i + 1][j].rgbtRed * 2) + (img[i][j].rgbtRed * 0));
                blueGy = ((img[i][j - 1].rgbtBlue * 0) + (img[i + 1][j - 1].rgbtBlue * 1) + (img[i + 1][j].rgbtBlue * 2) +
                          (img[i][j].rgbtBlue * 0));
                greenGy = ((img[i][j - 1].rgbtGreen * 0) + (img[i + 1][j - 1].rgbtGreen * 1) + (img[i + 1][j].rgbtGreen * 2) +
                           (img[i][j].rgbtGreen * 0));
            }

            //calculates the square root of Gx^2 + Gy^2 for each rgb channel values
            float red = sqrt((pow(redGx, 2)) + (pow(redGy, 2)));
            float blue = sqrt((pow(blueGx, 2)) + (pow(blueGy, 2)));
            float green = sqrt((pow(greenGx, 2)) + (pow(greenGy, 2)));
            //to cap the rgb channel values.
            int nred = fmin(round(red), 255);
            int nblue = fmin(round(blue), 255);
            int ngreen = fmin(round(green), 255);

            //stores the new values of the rgb channel
            image[i][j].rgbtGreen = ngreen;
            image[i][j].rgbtBlue = nblue;
            image[i][j].rgbtRed = nred;
        }
    }
    return;
}