#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
//              A  B  C  D  E  F  G  H  I  J  K  L  M  N  O  P  Q   R  S  T  U  V  W  X  Y  Z
//              65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80 81 82 83 84 85 86 87 88 89 90
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(char* word);
void print_winner(int score1, int score2);

int main(void)
{
    // Get input words from both players
    char word1[20]; 
    printf("Player 1: ");
    scanf("%s", word1);
    
    char word2[20]; 
    printf("Player 2: ");
    scanf("%s", word2);

    // Score both words
    int score1 = compute_score(word1);
    printf("%d\n", score1);

    int score2 = compute_score(word2);
    printf("%d\n", score2);

    // Print the winner
    print_winner(score1, score2);
}

// function definition
int compute_score(char* word)
{
    // Compute and return score for string
    int total = 0;
    int position;
    for (int i = 0; i < strlen(word); i++)
    {
        // change to uppercase then find location in array
        position = toupper(word[i]) - 65;

        // check is char is a letter
        if(isalpha(word[i]) == 0)
        {
            continue;
        }
        total += POINTS[position];
    }

    return total;
}

// function definition
void print_winner(int score1, int score2)
{
    // check to see which score is higher > print winner
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}