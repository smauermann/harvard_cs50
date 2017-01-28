#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ALPHABET 26


char* encrypt_text(int n, string p, char* q, int k);

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        int k = atoi(argv[1]);
        // get text to encode from user
        printf("plaintext: ");
        string p = get_string();
        
        // make sure a proper string was given from user
        if (p != NULL)
        {
            // length of string
            int n = strlen(p);
            /*create char array because strings is read-only, and
            modified letters cant be written to it*/
            char q[n];
            // do some magic and encrypt the user input
            char* c = encrypt_text(n, p, q, k);
            // give the user the encrypted text
            printf("ciphertext: %s\n", c);
            return 0;
        }
    }
    
    else
    {
        printf("Usage: ./caesar k\n");
        return 1;
    }
}

char* encrypt_text(int n, string p, char* q, int k)
{
    // iterate over text and manipulate each letter
    int start;
    for (int i = 0; i < n; i++)
    {
        // check if current element actually is alpha
        if (isalpha(p[i]))
        {
            /*compute where ASCII alphabet starts,
            upper at 65, lower case at 97*/
            start = isupper(p[i]) ? 65 : 97;
            /*pi - start + k = relative shift from starting letter,
            % ALPHABET = wrap around to the beginning of alphabet,
            + start = go from relative shift to absolute value for the ASCII letter*/
            q[i] = ((int) p[i] - start + k) % ALPHABET + start;
        }
        // if current string element is not a letter, dont modify it
        else
        {
            q[i] = p[i];
        }
    }
    
    return q;
}