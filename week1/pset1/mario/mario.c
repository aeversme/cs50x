#include <stdio.h>
#include <cs50.h>

//Prototype
void block(int n);

int main(void)
{
    printf("Thank you for using the Mario Pyramid Maker.\n");

    //Get a number between 1-8, inclusive.
    int height;
    do
    {
        height = get_int("Enter a height between 1-8: ");
    }
    while (height < 1 || height > 8);

    //Create mirrored pyramids of given height.
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (height - (i + 1)); j++)
        {
            printf(" ");
        }
        block(i + 1);
        printf("  ");
        block(i + 1);
        printf("\n");
    }
}

// Create correct number of blocks.
void block(int n)
{
    for (int k = 0; k < n; k++)
    {
        printf("#");
    }
}