#include <stdio.h>
// #include <cs50.h>

int main(void)
{
    // a variable declaration of a string is a pointer to the address of the first character

    char *s = "HI!"; //can also be written as string s = "HI!"; with #include <cs50.h>
    // printf("%p\n", &s[0]); // can also be written as printf("%p\n", s);
    // printf("%p\n", &s[1]);
    // printf("%p\n", &s[2]);

    printf("%c\n", *s); // prints "H"
    printf("%c\n", *(s + 1)); // prints "I"

    // printf("%c\n", s[1]); // prints "I"
    // printf("%c\n", s[2]);
}

// typedef char *string;