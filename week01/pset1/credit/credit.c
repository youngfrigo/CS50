#include <stdio.h>

// function prototypes
int get_card_length(long card_number);
int calc_2nd_digit(long card_number);
int calc_last_digit(long card_number);
void check_card(long card_number, int a, int b, int c);

long amex = 378282246310005;
long mastercard = 5555555555554444;
long visa = 4111111111111111;

int main (void)
{
    // set card number
    long card_number = mastercard;

    int a = calc_2nd_digit(card_number);
    int b = calc_last_digit(card_number);
    int c = get_card_length(card_number);     
    check_card(card_number, a, b, c);
}

// function definition
int get_card_length(long card_number)
{
    int card_len = 0;
    // loop to check amount of digits
    while ((float) card_number / 10 > 0)
    {
        card_number /= 10;
        card_len++;
    }
    return card_len;
}

// function definition
int calc_2nd_digit(long card_number)
{
    // variables needed
    int buffer = 0;
    int buffer_2 = 0;
    int final_sum = 0;
    card_number /= 10;

    // loop to caculate checksum
    while (card_number > 0)
    {
        buffer = card_number % 10;
        buffer_2 = buffer * 2;

        if (buffer_2 < 10)
        {
            final_sum += buffer_2;
        }
        else
        {
            // if the multiplied valie is greater than 10, get sum of individual digits
            buffer_2 = (buffer_2 %10) + (buffer_2 / 10);
            final_sum += buffer_2;
        }

        // loop to get to next number in checksum
        for (int i = 0; i < 2; i++)
        {
            card_number /= 10;
        }
    }
    return final_sum;
}

// function definition
int calc_last_digit(long card_number)
{
    // variable needed
    int final_sum = 0;

    // loop to caculate checksum
    while (card_number > 0)
    {
        // assign last digit to final_sum
        final_sum += card_number % 10;

        // loop to get to the next number in the checksum
        for (int i = 0; i < 2; i++)
        {
            card_number /= 10;
        }
    }
    return final_sum;
}

// function definition
void check_card(long card_number, int a, int b, int c)
{
    // variables needed
    int first_two_digit;
    int first_digit;

    // loop to get first digit and first two digits
    for (int i = 0; i < c; i++)
    {
        card_number /= 10;

        if (card_number < 10 && card_number > 0)
        {
            // if card_num < 10 we're at the first digit
            first_digit = card_number;
        }
        else if (card_number < 100 && card_number > 10)
        {
            // if card_num < 100 we're at the first two digits
            first_two_digit = card_number;
        }
    }

    // if statements to print out card type
    if (first_digit == 4 && (c == 13 || c == 16))
    {
        printf("VISA\n");
    }
    else if ((first_two_digit >= 51 && first_two_digit <= 55) && c == 16)
    {
        printf("MASTERCARD\n");
    }
    else if((first_two_digit == 34 || first_two_digit == 37) && c == 15)
    {
        printf("AMEX\n");
    }

    // if statement to check if card is INVALID
    if ((a + b) % 10 != 0 || (c < 13 || c > 16))
    {
        printf("INVALID\n");
    }
}