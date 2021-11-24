#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// Prototypes
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
int coleman_liau(int letters, int words, int sentences);

int main(void)
{
    // Prompt user for a string of text using get_string
    string text = get_string("Text: ");

    // Calulate number of letters, words, and sentences in the text.
    int letter_count = count_letters(text);
    int word_count = count_words(text);
    int sentence_count = count_sentences(text);

    // Get grade index using Coleman-Liau algorithm
    int index = coleman_liau(letter_count, word_count, sentence_count);

    // Output = "Grade x" where x is grade level computed by Coleman-Liau forumla
    // If x <= 16, print "Grade 16+"; if x < 1, print "Before Grade 1"
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

int count_letters(string text)
{
    // Count the number of letters in the text, not counting spaces or symbols.
    int count = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]))
        {
            count += 1;
        }
    }
    return count;
}

int count_words(string text)
{
    // Count the number of words in the text.
    int count = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isspace(text[i]))
        {
            count += 1;
        }
    }
    // There will be 1 more word than there are number of spaces in the text.
    return count + 1;
}

int count_sentences(string text)
{
    // Count the number of sentences in the text, based on punctuation. Include cases like 'Mr.' and 'Mrs.'.
    int count = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            count += 1;
        }
    }
    return count;
}

int coleman_liau(int letters, int words, int sentences)
{
    // index = 0.0588 * L - 0.296 * S - 15.8 where L is avg # of letters per 100 words and S is avg # of sentences per 100 words
    float L = (letters * 100.0) / words;
    float S = (sentences * 100.0) / words;

    int index = round((0.0588 * L) - (0.296 * S) - 15.8);
    return index;
}