#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// max number of candidates
#define MAX 9

// for malloc
int n = 256;

// number of candidates global variables
int candNum;

// number of voters
int numVoters;

// define candidate type
typedef struct candidate
{
    char *name;
    int votes;
}
candidate;

// array of candidates
candidate candidates[MAX];

// function prototypes
bool voteCheck(char *name);
void printWinner(void);

int main(int argc, char *argv[])
{
    candNum = argc - 1;

    // ensure that correct amounts of commands are entered
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }
    else if (argc > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }

    // iterate through each letter to ensure on alphabetic characters are used
    for (int i = 1; i < argc; i++)
    {
        int n = strlen(argv[i]);
        for (int j = 0; j < n; j++)
        {
            if (!(isalpha(argv[i][j])))
            {
                printf("Invalid names\n");
                return 1;
            }
        }
    }

    // load names into array and set votes to zero
    for (int i = 1; i < argc; i++)
    {
        candidates[i - 1].name = malloc(sizeof(char) * 256);
        candidates[i - 1].name = argv[i];
        candidates[i - 1].votes = 0;
    }

    // prompt user for number of voters
    printf("Number of voters: ");
    scanf("%i", &numVoters);

    for (int i = 0; i < numVoters; i ++)
    {
        // variable for votest that are cast
        char *castVote = malloc(sizeof(char) * 256);

        printf("Vote: ");
        scanf("%s", castVote);
        
        if (!voteCheck(castVote))
        {
            printf("Invalid vote\n");
            i--;
        }
    }
}

// function definition
bool voteCheck(char *name)
{
    for (int i = 0; i < numVoters; i++)
    {
        for (int j = 0; j < candNum; j++)
        {
            if (strcmp(name, candidates[j].name) == 0)
            {
                candidates[j].votes++;
                return true;
            }
        }
    }
    return false;
}

// function definition
void printWinner(void)
{
    // variables to track of winning votes and winner
    char *winner = malloc(sizeof(char) * 256);
    int winVote = 0;

    // establish winning number of votes
    for (int i = 0; i < candNum - 1; i++)
    {
        if (candidates[i].votes > winVote)
        {
            winVote = candidates[i].votes;
        }
    }

    // print the name of the candidates that have that many votes
    for (int i  = 0; i < candNum; i++)
    {
        if (candidates[i].votes == winVote)
        {
            printf("%s\n", candidates[i].name);
        }
    }
}