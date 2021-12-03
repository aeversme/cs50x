#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(void)
{
    // create a pointer to a file
    FILE *file = fopen("phonebook.csv", "a");
    if (file == NULL)
    {
        return 1;
    }

    char *name = get_string("Name: ");
    char *number = get_string("Number: ");

    // print to a file
    // inputs: (pointer to file, format string, variables)
    fprintf(file, "%s,%s\n", name, number);

    // close a file
    fclose(file);
}