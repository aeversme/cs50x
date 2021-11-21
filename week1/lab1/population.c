#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int start;
    do
    {
        start = get_int("Enter a starting population size (9 or greater): ");
    }
    while (start < 9);

    // TODO: Prompt for end size
    int final;
    do
    {
        final = get_int("Enter a final population size larger than the starting size: ");
    }
    while (final < start);

    // TODO: Calculate number of years until we reach threshold
    if (final == start)
    {
        printf("Years: 0\n");
    }
    else
    {
        int years;
        int endyear = 0;
        for (years = 0; endyear < final; years++)
        {
            endyear = start + (start / 3) - (start / 4);
            start = endyear;
        }

        // TODO: Print number of years
        printf("Years: %i\n", years);
    }
}
