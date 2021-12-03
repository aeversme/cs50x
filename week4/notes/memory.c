#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char *s = malloc(3);
    s[0] = 'H';
    s[1] = 'I';
    s[2] = '!';
    s[3] = '\0';
    printf("%s\n", s);
}

// Using valgrind ./memory:
// Invalid write on line 10 - only 3 bytes allocated to s
// Invalid read on line 11
// Memory leak (free() not called)