#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(void)
{
    char *s = get_string("s: ");

    // Allocate a certain # of bytes in memory
    // in this case, strlen(s) + 1 leaves space for the
    // nul ("\0") character at the end of s
    // malloc requires <stdlib.h>
    char *t = malloc(strlen(s) + 1);

    // Does t have a valid address? (Is there enough space allocated in memory?)
    if (t == NULL)
    {
        // Null pointer (address 0), so exit
        return 1;
    }

    // i <= n includes the nul ("\0") character at the end of s
    // for (int i = 0, n = strlen(s); i <= n; i++)
    // {
    //     t[i] = s[i]; // can also be written *(t + 1) = *(s + 1);
    // }

    // arguments are (destination, source)
    strcpy(t, s);

    // Is there a string in t?
    if (strlen(t) > 0)
    {
        // String, so capitalize the first character
        t[0] = toupper(t[0]); // can also be written as *t = toupper(*t);
    }

    printf("s: %s\n", s);
    printf("t: %s\n", t);

    // Release allocated memory
    // input argument is (output of malloc)
    free(t);
}