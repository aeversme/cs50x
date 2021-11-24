#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

// Global contstants
const int UPPER_ADJ = 65;
const int LOWER_ADJ = 97;

// Prototypes
bool is_valid_key(string key);
bool is_duplicate_letter(char letter, string array);
string encode_plaintext(string plaintext, char *ciphertext, string cipher_key);

int main(int argc, string argv[])
{
    // Check for exactly two args; return 1 if # of args is wrong
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    // Check for valid key; return 1 if not valid
    else if (! is_valid_key(argv[1]))
    {
        return 1;
    }
    // Prompt for plaintext; return ciphertext and exit code 0
    else
    {
        string cipher_key = argv[1];
        string plaintext = get_string("plaintext: ");
        // Create buffer for ciphertext array
        char ciphertext[strlen(plaintext) + 1];
        printf("ciphertext: %s\n", encode_plaintext(plaintext, ciphertext, cipher_key));
        return 0;
    }
}

bool is_valid_key(string key)
{
    int key_length = strlen(key);

    // Check that the key is the correct length
    if (key_length != 26)
    {
        printf("Key must contain exactly 26 alphabetical characters.\n");
        return false;
    }
    else
    {
        char key_check[27];
        for (int i = 0; i < key_length; i++)
        {
            key_check[i] = '\0';

            // Check for any non-alphabetical characters
            if (! isalpha(key[i]))
            {
                printf("Key must contain only alphabetical characters.\n");
                return false;
            }
            // Check for duplicate letters
            else if (is_duplicate_letter(key[i], key_check))
            {
                printf("Key must not contain duplicate letters.\n");
                return false;
            }
            // Add current character to key_check array for duplication checking
            else
            {
                key_check[i] = key[i];
            }
        }
    }
    return true;
}

bool is_duplicate_letter(char letter, string array)
{
    // Check if a given letter exists in a given array; if it does, return true
    for (int i = 0, n = strlen(array); i < n; i++)
    {
        if (letter == array[i])
        {
            return true;
        }
    }
    return false;
}

string encode_plaintext(string plaintext, char *ciphertext, string cipher_key)
{
    // Encode the plaintext input, preserving the case of each plaintext letter
    // Ciphertext buffer being passed in must be equal to or larger than the size of the expected output

    int plaintext_length = strlen(plaintext);
    
    // Set final character of the array to null
    ciphertext[plaintext_length] = '\0';

    for (int i = 0; i < plaintext_length; i++)
    {
        char p = plaintext[i];

        // If the plaintext character is not a letter, output the character to ciphertext
        if (! isalpha(p))
        {
            ciphertext[i] = p;
        }
        // If the plaintext character is uppercase, output the appropriate ciphertext letter in uppercase
        else if (isupper(p))
        {
            int index = p - UPPER_ADJ;
            ciphertext[i] = toupper(cipher_key[index]);
        }
        // If the plaintext character is lowercase, output the appropriate ciphertext letter in lowercase
        else
        {
            int index = p - LOWER_ADJ;
            ciphertext[i] = tolower(cipher_key[index]);
        }
    }

    return ciphertext;
}