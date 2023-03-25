#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// maximum number of candidates
#define MAX 9

// max number of characters
int n = 256;

// number of candidates
int cand_num;

// voter preferences
int voterChoices = 3;

// preference data type
typedef struct
{
    char *first;
    char *second;
    char *third;
}
votes;

// candidate data type
typedef struct
{
    char *name;
    int votes;
    bool eliminated;
}
candidate;

// array to hold candidates
candidate candidates[MAX];

// function prototype
void getVotes(int numOfVoters, votes voters[]);
void printVotes(votes voters[]);

int main(int argc, char *argv[])
{
    // choices variables
    char *first = malloc(sizeof(char) * n);
    char *second = malloc(sizeof(char) * n);
    char *third = malloc(sizeof(char) * n);

    cand_num = argc - 1;

    // error checking commads
    if (argc < 2)
    {
        printf("Usage: ./runoff [candidate ...]\n");
        return 1;
    }
    else if (argc > 9)
    {
        printf("Maxinum number of candidates is %i\n", MAX);
        return 2;
    }
    
    // ensuring user enters only alphabetic characters
    for (int i = 1; i < argc; i++)
    {
        int len = strlen(argv[i]);
        for (int j = 0; j < len; j++)
        {
            if (!isalpha(argv[i][j]))
            {
                printf("Candidate names must be alphabetic\n");
                return 3;
            }
        }
    }

    // load names in to an array and set votes to 0
    for (int i = 1; i < argc; i++)
    {
        candidates[i - 1].name = malloc(sizeof(char) * n);
        candidates[i - 1].name = argv[i];
        candidates[i - 1].votes = 0;
    }
    
    // prompt user for the number of voters
    int numOfVoters;
    printf("Number of voters: ");
    scanf("%i", &numOfVoters);

    votes voters[numOfVoters];

    getVotes(numOfVoters, voters);

    printf("%s\n", candidates[0].name);
    printf("%s\n", candidates[1].name);
    printf("%s\n", candidates[2].name);

    printVotes(voters);

}

void getVotes(int numOfVoters, votes voters[])
{
    for (int i = 0; i < numOfVoters; i++)
    {
        // prepare user to enter preferences
        printf("Voter %i Ranking\n", i + 1);

        // variable to hold vote
        char *castVote = malloc(sizeof(char) * n);

        // loop to iterate over preferences
        for (int j = 0; j < voterChoices; j++)
        {
            // variables to ensure 
            int matches = 0;
            printf("Vote %i: ", j + 1);
            scanf("%s", castVote);
            printf("%s\n", castVote);
            for (int k = 0; k < cand_num; k++)
            {
                if (strcmp(candidates[k].name, castVote) == 0)
                {
                    if (j == 0)
                    {
                        voters[i].first = castVote;
                        printf("Voter 1 - Choice 1: %s\n", voters[i].first);
                        matches++;
                    }
                    else if (j == 1)
                    {
                        voters[i].second = castVote;
                        printf("Voter 1 - Choice 2: %s\n", voters[i].second);
                        matches++;
                    }
                    else if (j == 2)
                    {
                        voters[i].third = castVote;
                        printf("Voter 1 - Choice 3: %s\n", voters[i].third);
                        matches++;
                    }
                }
            }
            if (matches == 0)
            {
                printf("Invalid vote.\n");
                j--;
            }
        }
    }
}

void printVotes(votes voters[])
{
    for (int i = 0; i < 1; i++)
    {
        printf("Voter 1 - Choice 1: %s\n", voters[i].first);
        printf("Voter 1 - Choice 2: %s\n", voters[i].second);
        printf("Voter 1 - Choice 3: %s\n", voters[i].third);
    }
}