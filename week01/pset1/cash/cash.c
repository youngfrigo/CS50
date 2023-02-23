#include <stdio.h>

// declare function prototypes
int get_change(void);
int calc_quarters(int change);
int calc_dimes(int change);
int calc_nickels(int change);
int calc_pennies(int change);

int main(void)
{
    // declare variables
    int change;
    int quarters;
    int dimes;
    int nickels;
    int pennies;
    int total_coins;

    // prompt user for change
    change = get_change();

    // run quarters function
    quarters = calc_quarters(change);
    change -= quarters * 25;
    printf("Quarters: %i\n", quarters);

    // run dimes function
    dimes = calc_dimes(change);
    change -= dimes * 10;
    printf("Dimes: %i\n", dimes);

    // run nickels function
    nickels = calc_nickels(change);
    change -= nickels * 5;
    printf("Nickels: %i\n", nickels);

    // run pennies function
    pennies = calc_pennies(change);
    change -= pennies * 1;
    printf("Pennies: %i\n", pennies);

    total_coins = quarters + dimes + nickels + pennies;

    printf("Total coins: %i\n", total_coins);
}

// define functions
int get_change(void)
{
    int change;
    do
    {
        printf("How much change are you owed: ");
        scanf("%i", &change);
    }
    while (change <= 0);
    return change;
}

int calc_quarters(int change)
{   
int x = 0;
while (change >= 25)
{
    change -= 25;
    x += 1;
}
return x;
}

int calc_dimes(int change)
{   
    int x = 0;
    while (change >= 10)
    {
        change -= 10;
        x += 1;
    }
    return x;
}

int calc_nickels(int change)
{   
    int x = 0;
    while (change >= 5)
    {
        change -= 5;
        x += 1;
    }
    return x;
}

int calc_pennies(int change)
{   
    int x = 0;
    while (change >= 1)
    {
        change -= 1;
        x += 1;
    }
    return x;
}