#include <stdio.h>
#include <cs50.h>

int is_valid_cardnumber(char *array, int length);

int main(void)
{
    // Get credit card number input using get_long
    long card_number = get_long("Enter a credit card number: ");

    // Insert the number into a string array
    char cc_string[50];
    int length = sprintf(cc_string, "%ld", card_number);

    // Check the length of the input
    if (length < 13 || length > 16)
    {
        printf("INVALID\n");
    }
    else
    {
        // Check for card number validity
        if (! is_valid_cardnumber(cc_string, length))
        {
            printf("INVALID\n");
        }
        // If valid, return card brand based on leading number(s)
        else
        {
            if (cc_string[0] == '3' && (cc_string[1] == '4' || cc_string[1] == '7'))
            {
                printf("AMEX\n");
            }
            else if (cc_string[0] == '5' && (cc_string[1] >= '1' && cc_string[1] <= '5'))
            {
                printf("MASTERCARD\n");
            }
            else if (cc_string[0] == '4')
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
    }
}

// Evaluate whether the given array contains a valid credit card number
int is_valid_cardnumber(char *array, int length)
{
    bool is_number_valid = false;

    // Check for correct leading number
    if (array[0] == '3' || array[0] == '4' || array[0] == '5')
    {
        int mult_every_other = 0;
        int add_every_other = 0;

        // Check whether array length is even or odd and set starting indices appropriately
        int mult_index = 0;
        int add_index = 1;
        bool length_is_odd = (bool)(length & 0x01);
        if (length_is_odd)
        {
            mult_index = 1;
            add_index = 0;
        }

        // Multiply every other digit by 2, starting with the number’s second-to-last digit, and then add those products’ digits together.
        for (int i = mult_index; i < length; i += 2)
        {
            int doubled_digit = 2 * ((int)array[i] - '0');
            if (doubled_digit < 10)
            {
                mult_every_other += doubled_digit;
            }
            else
            {
                int tens_digit = doubled_digit / 10;
                int ones_digit = doubled_digit % 10;
                mult_every_other += (tens_digit + ones_digit);
            }
        }

        // Add the sum to the sum of the digits that weren’t multiplied by 2.
        for (int j = add_index; j < length; j += 2)
        {
            add_every_other += ((int)array[j] - '0');
        }

        // If the total’s last digit is 0 (or, put more formally, if the total modulo 10 is congruent to 0), the number is valid!
        int total = mult_every_other + add_every_other;
        if (total % 10 == 0)
        {
            is_number_valid = true;
        }
    }

    // Return true or false, defaults to false
    return is_number_valid;
}
