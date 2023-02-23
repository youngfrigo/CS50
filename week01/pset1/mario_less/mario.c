#include <stdio.h>

int main(void)
{
    int height;

    // prompt user for the height of the pyramid
    do
    {
        printf("Height of the pyramid: ");
        scanf("%i", &height);

    } while (height <= 0 || height > 8);

    int x = height;

    // for loop to determine the height of the pyramid
    for (int i = 0; i <= x - 1; i++) 
    {
        for (int j = 0; j <= x - 1; j++)
        {
            if (i + j >= x - 1)
            {
                printf("#");
            }
            else
            {
                printf(" ");
            }
            
        }
        printf("\n");
    }
}

//   0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16
// 0 . . . . . . . # . #  .  .  .  .  .  .  .
// 1 . . . . . . # # . #  #  .  .  .  .  .  .
// 2 . . . . . # # # . #  #  #  .  .  .  .  .
// 3 . . . . # # # # . #  #  #  #  .  .  .  .
// 4 . . . # # # # # . #  #  #  #  #  .  .  .
// 5 . . # # # # # # . #  #  #  #  #  #  .  .
// 6 . # # # # # # # . #  #  #  #  #  #  #  .
// 7 # # # # # # # # . #  #  #  #  #  #  #  # 