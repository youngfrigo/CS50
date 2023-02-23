#include <stdio.h>

// declaration of prototype function
int calculator(int a, int b, int c);

int main(void)
{

    // declare necessary variables
    int start_size;
    int end_size;
    int years = 0;

    // do while loop to ensure starting number is greater than 9
    do
    {
        // prompt user for starting number again
        printf("Start size: ");

        // scan and assign again
        scanf("%i", &start_size);

    }
    while (start_size < 9);


    // do while loop to ensure end number is greater than starting number
    do
    {
        // prompt user again
        printf("End size: ");

        // assign input the end size
        scanf("%i", &end_size);
    }
    while (end_size < start_size);

    // if both numbers are equal return 0
    if (end_size == start_size)
    {
        printf("Years: 0");
    }

    // print result of calculator function
    printf("Years: %i\n", calculator(start_size, end_size, years));
}

// function definition
int calculator(int a, int b, int c)
{
    int current = a;
    int goal = b;

    while (current < goal)
    {
        int new_pop = current + (current / 3) - (current / 4);
        current = new_pop;
        c++;
    }
    return c;
}