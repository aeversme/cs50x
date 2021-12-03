#include <stdio.h>

// int main(void)
// {
//     int x;
//     printf("x: ");
//     scanf("%i", &x);
//     printf("x: %i\n", x);
// }

// scanf does not include error checking

int main(void)
{
    // MUST initialize s, either with char *s = malloc(x); or char s[x];
    char s[4];
    printf("s: ");
    scanf("%s", s);
    printf("s: %s\n", s);
    // if initializing with malloc, MUST use free(s);
}