#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
// Decimal value of lowercase ASCII character 'a'
int LOWER_A = 97;

// Prototype
int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // Print the winner
    if (score1 == score2)
    {
        printf("Tie!\n");
    }
    else if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else
    {
        printf("Player 2 wins!\n");
    }
}

int compute_score(string word)
{
    int score = 0;
    int index = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        char current_char = word[i];

        // If character is not a letter, add zero to score
        if (! isalpha(current_char))
        {
            score += 0;
        }
        else
        {
            // Check if character is upper; if so, convert to lower
            if (isupper(current_char))
            {
                current_char = tolower(current_char);
            }

            // Set 'index' to character ascii value - LOWER_A
            index = current_char - LOWER_A;

            // Add value of POINTS[index] to 'score'
            score += POINTS[index];
        }
    }
    return score;
}