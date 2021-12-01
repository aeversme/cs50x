#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // This code only runs one time to initialize all values
    // in the preferences array to 0
    static bool initialized = false;
    if (!initialized)
    {
        initialized = true;
        for (int i = 0; i < MAX; i++)
        {
            for (int j = 0; j < MAX; j++)
            {
                preferences[i][j] = 0;
            }
        }

        // Example of initializing using pointers
        if (false)
        {
            int *p = (int *) preferences;
            for (int i = 0; i < MAX * MAX; i++, p++)
            {
                *p = 7;
            }
        }
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count - 1; i++)
    {
        int candidate_index = ranks[i];
        for (int j = i + 1; j < candidate_count; j++)
        {
            int other_candidate = ranks[j];
            // Candidate ranked ahead of other candidate
            preferences[candidate_index][other_candidate]++;
        }
    }

    if (false)
    {
        for (int i = 0; i < candidate_count; i++)
        {
            for (int j = 0; j < candidate_count; j++)
            {
                printf("preferences[%i][%i] = %i\n", i, j, preferences[i][j]);
            }
        }
    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // Loop through preferences
    // Create a "pair" if one candidate is preferred
    // i.e. preferences[1][2] > preferences[2][1]
    // increment pair_count if a preference is found & add each pair to pairs array as pairs[pair_count]
    pair_count = 0;

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (i != j)
            {
                if (preferences[i][j] > preferences[j][i])
                {
                    // add pair to pairs[pair_count]
                    // winner = i, loser = j
                    pairs[pair_count].winner = i;
                    pairs[pair_count].loser = j;
                    // increment pair count
                    pair_count++;
                }
                else
                {
                    // if there is a tie, no pair is added to pairs
                }
            }
        }
    }
    if (false)
    {
        for (int i = 0; i < pair_count; i++)
        {
            printf("pair %i: winner %i loser %i\n", i, pairs[i].winner, pairs[i].loser);
        }
    }

    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // for each pair
    // determine strength of victory (pref[win][los] - pref[los][win])
    // add to int strength[i]

    // for test case in votes.txt:
    // pairs = [[0,1], [0,2], [1,2]]
    // strength = [7, 3, 5]

    int strength[pair_count];

    for (int i = 0; i < pair_count; i++)
    {
        strength[i] = preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner];
    }

    if (false)
    {
        for (int i = 0; i < pair_count; i++)
        {
            printf("strength[%i]: %i\n", i, strength[i]);
        }
    }

    // sort strength array & perform same swaps on pairs array in parallel
    // need: int swap_count, pair temp_pair, int temp_strength

    int swap_count = -1;
    int final_index = pair_count;
    while (swap_count != 0)
    {
        swap_count = 0;
        final_index--;
        for (int i = 0; i < final_index; i++)
        {
            pair temp_pair;
            int temp_strength;
            if (strength[i + 1] > strength[i])
            {
                temp_strength = strength[i];
                strength[i] = strength[i + 1];
                strength[i + 1] = temp_strength;
                temp_pair = pairs[i];
                pairs[i] = pairs[i + 1];
                pairs[i + 1] = temp_pair;
                swap_count++;
            }
        }
    }

    if (false)
    {
        for (int i = 0; i < pair_count; i++)
        {
            printf("sorted strength[%i]: %i\n", i, strength[i]);
        }
    }

    return;
}

bool would_loop(start, end)
{
    int intermediate = 0;

    if (start == end)
    {
        return true;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (i != start)
        {
            if (locked[i][start])
            {
                intermediate = i;
                if (would_loop(intermediate, end))
                {
                    return true;
                }
            }
        }
    }
    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        // Does this pair cause a loop?
        if (! would_loop(pairs[i].winner, pairs[i].loser))
        {
            // No loop, so add the pair to locked
            locked[pairs[i].winner][pairs[i].loser] = true;
        }

        // Debugging printf statements
        // printf("Pair evaluated: %i, %i\n", pairs[i].winner, pairs[i].loser);
        // for (int j = 0; j < candidate_count; j++)
        // {
        //     for (int k = 0; k < candidate_count; k++)
        //     {
        //         printf("%i ", locked[j][k] ? 1 : 0);
        //     }
        //     printf("\n");
        // }
    }

    return;
}

// Print the winner of the election
void print_winner(void)
{
    for (int j = 0; j < candidate_count; j++)
    {
        bool winner = true;
        for (int i = 0; i < candidate_count; i++)
        {
            if (locked[i][j])
            {
                winner = false;
                // could break; if no logic errors
            }
        }
        if (winner)
        {
            printf("%s\n", candidates[j]);
            // could break; if no logic errors
        }
    }
    return;
}

