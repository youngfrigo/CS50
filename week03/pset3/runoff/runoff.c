#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// maximum number of candidates
#define MAX 9
#define MAX_VOTERS 100

// max number of characters
int n = 256;

// number of candidates and voters
int candNum;
int numOfVoters;

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
int preferences[MAX_VOTERS][MAX];

// function prototypes
int checkNames(char *name, candidate candidates[]);
void getVotes(void);
void tabulateVotes(void);
bool printWinner(void);
int findMin(void);
void eliminate(int min);
bool isTie(int min);

int main(int argc, char *argv[])
{
    candNum = argc - 1;

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
        candidates[i - 1].eliminated = false;
    }
    
    // prompt user for the number of voters
    printf("Number of voters: ");
    scanf("%i", &numOfVoters);

    // function call to prompt and save votes
    getVotes();

    while (true)
    {
        // calculate all votes
        tabulateVotes();

        // if a winner has been found, stop the loop
        bool win = printWinner();
        if(win)
        {
            break;
        }

        // calculate the lowest amount of votes
        int min = findMin();

        // check to see if there is a tie between un-eliminated candidates
        bool tie = isTie(min);
        if (tie)
        {
            for (int i = 0; i < candNum; i++)
            {
                if (candidates[i].eliminated == false)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // eliminate any candidates with the current lowest amount of votes
        eliminate(min);

        // reset all votes back to zero
        for (int i = 0; i < candNum; i++)
        {
            candidates[i].votes = 0;
        }
    }

}

// function definition
int checkNames(char *name, candidate candidates[])
{
    // iterate through cast vote and candidates to compare
    for (int i = 0; i < candNum; i++)
    {
        if (strcmp(candidates[i].name, name) == 0 && candidates[i].eliminated == false)
        {
            return i;
        }
    }
    return 404;
}

// function definition
void getVotes(void)
{
    // loop to ask number each voter for their preferences
    for (int i = 0; i < numOfVoters; i++)
    {
        // iterate through the number of candidates to ensure all preferences are taken
        for (int j = 0; j < candNum; j++)
        {
            // variable to hold current vote
            char *castVote = malloc(sizeof(char) * n);

            printf("Vote %i: ", j + 1);
            scanf("%s", castVote);

            // function to ensure name matches a candidate
            if (checkNames(castVote, candidates) == 404)
            {
                printf("Invalid vote.\n");
                j--;
                continue;
            }
            // if the name matches, take the first preference of that voter and increase their votes by
            else
            {
                // first preference of each voter is
                int pos = checkNames(castVote, candidates);
                preferences[i][j] = pos;
            }
        }
    }
}

// function definition
bool printWinner()
{
    for (int i = 0; i < candNum; i++)
    {
        if (candidates[i].votes > numOfVoters / 2)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

// function definition
void tabulateVotes()
{
    // iterate for each voter
    for (int i = 0; i < numOfVoters; i++)
    {
        for (int j = 0; j < candNum; j++)
        {
            // position of preference
            int pos = preferences[i][j];

            // increment the vote of the first choice for each voter
            if (candidates[pos].eliminated == false)
            {
                candidates[pos].votes++;
                break;
            }
            else
            {
                continue;
            }
        }
    }
}

// function definition
int findMin(void)
{
    int min = numOfVoters / 2;
    for (int i = 0; i < candNum; i++)
    {
        if (candidates[i].eliminated == false && candidates[i].votes < min)
        {
            min = candidates[i].votes;
        }
    }
    return min;
}

// function definition
void eliminate(int min)
{
    for (int i = 0; i < candNum; i++)
    {
        if (candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
}

// function definition
bool isTie(int min)
{
    bool tie = false;
    for (int i = 0; i < candNum; i++)
    {
        if (candidates[i].eliminated == false && candidates[i].votes == min)
        {
            tie = true;
        }
        else if (candidates[i].eliminated == false && candidates[i].votes != min)
        {
            tie = false;
        }
    }
    return tie;
}