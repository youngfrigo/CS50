#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int byte = 8;

int main(void)
{
    char h[] = "Hello!";

    int n = strlen(h);
    int array[byte];
    int temp;

    for (int i = 0; i < n; i++)
    {
        int c = h[i];
        for (int j = 0; j < byte; j++)
        {   
            if (c >= 0)
            {
                array[j] = c % 2;
                c /= 2;
                printf("%i", array[j]);
            }
        }
        printf("\n");
    }
}

// 33 16  8  4  2  1  0
//  1  0  0  0  0  1  0