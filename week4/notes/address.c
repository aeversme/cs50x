#include <stdio.h>

int main(void)
{
    // * = "go to" operator (dereference)
    // & = "address of" operator

    // the address of this variable can and probably will change
    // each time the function is called
    int n = 50;

    // pointer = variable that stores the address of a value
    // pointer needs to have the type of the variable it's pointing to
    // this pointer's type is "int *"
    int *p = &n;

    // %p = pointer (print the address)
    // printing *p prints the value at the pointer's address
    printf("%i\n", *p);
}