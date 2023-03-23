#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 9

int n = 256;

typedef struct candidate
{
    char *name;
    int votes;
}
candidate;

// ./plurality Alice Bob Charlie
//      0        1    2     3
int main(int argc, char *argv[])
{
    int numVoters = 0;
    int candNum = argc - 1;
    candidate candidates[candNum];

    // prompt user for number of voters
    printf("Number of voters: ");
    scanf("%i", &numVoters);

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

    for (int i = 1; i < argc; i++)
    {
        candidates[i - 1].name = malloc(sizeof(char) * 256);
        candidates[i - 1].name = argv[i];
        candidates[i - 1].votes = 0;
    }

    char *castVote = malloc(sizeof(char) * 256);

    for (int i = 0; i < numVoters; i++)
    {
        int matches = 0;
        printf("Vote: ");
        scanf("%s", castVote);
        for (int j = 0; j < candNum; j++)
        {
            if (strcmp(castVote, candidates[j].name) == 0)
            {
                candidates[j].votes++;
                matches++;
            }
        }
        if (matches == 0)
        {
            printf("Invalid vote\n");
            i--;
        }
    }

    char *winner = malloc(sizeof(char) * 256);
    int winVote = 0;
    for (int i = 0; i < candNum - 1; i++)
    {
        winVote = candidates[i].votes;
        winner = candidates[i].name;
        if (candidates[i + 1].votes > candidates[i].votes)
        {
            winVote = candidates[i + 1].votes;
            winner = candidates[i + 1].name;
        }
    }
    
    printf("%s\n", winner);
}
