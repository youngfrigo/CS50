#include <stdio.h>

int main(void)
{
    int height;

    // prompt user for for a height between 1 and 8
    do
    {
        printf("Please input height of the pyramid: ");
        scanf("%d", &height);
    }
    while (height <= 0 || height > 8);

    // assign height to simpler variable
    int x = height;

    // for loop to print out newlines == height
    for (int i = 0; i <= x - 1; i++)
    {
        // since this is going to be a larger and longer pyramid
        // we need to iterate more characters per line
        // number of characters per line is equal to (height * 2) + 1
        for (int j = 0; j <= x * 2; j++)
        {
            // print a space:
            // wherever i + j is less than height -1
            // wherever i == height - this is for the separation line in the middle
            if ((i + j) < (x - 1) || j == x)
            {
                printf(" ");

                // print an additional space in the middle column
                if (j == x)
                {
                    printf(" ");
                }
            }
            // if none of the above conditions are true, print "#
            else if ((j - i) <= (x + 1))
            {
                printf("#");
            }
        }
        printf("\n");
    }
}