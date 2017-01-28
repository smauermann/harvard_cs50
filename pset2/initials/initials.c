#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>


int main(void)
{
    // get name from user
    string name = get_string();
    
    // check if user provided a valid string, if not stop and return error code
    if (name == NULL)
    {
        return 1;
    }
    
    // iterate over user provided name, and print first char of char groups separated by whitespaces
    int skip = 0;
    for (int i = 0, n = strlen(name); i < n; i++)
    {
        // check quality of current string element: letter or space
        if (name[i] != ' ')
        {
            // only print the first letter of the name (skip = 0)
            // and set skip = 1 after printing
            if (!skip)
            {
                printf("%c", toupper(name[i]));
                skip = 1;
        }
            }
        // else covers if current element is a space, ie we left the current word
        // and the next letter we stumble upon needs to be printed
        else
        {
            skip = 0;
        }
    }
    printf("\n");
}
