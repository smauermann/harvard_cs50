#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET 26

int all_alpha(string s);
char encrypt_text(string plain, int *key_int, int nk, char *cipher);
int key_to_int(string k, int *key_int);


int main(int argc, string argv[])
{
    /* make sure exactly one command line argument was passed,
    firt element of argv[] is the script name itself */
    if (argc == 2)
    {
        // make sure the key k is all alphas and nothin else
        string key = argv[1];
        if (all_alpha(key))
        {
            // get string to encode from user
            printf("plaintext: ");
            string plain = get_string();
        
            // make sure a proper string was given from user
            if (plain != NULL)
            {
                // translate keyword into int array, preallocate buffer key_int
                int nk = strlen(key);
                int key_int[nk];
                key_to_int(key, key_int);
                
                /* do some magic and encrypt the user input,
                preallocate buffer for cipher array */
                char cipher[strlen(plain)];
                encrypt_text(plain, key_int, nk, cipher);
                
                // give the user the encrypted text
                printf("ciphertext: ");
                for (int i = 0, np = strlen(plain); i < np; i++)
                {
                    printf("%c", cipher[i]);
                }
                printf("\n");
                return 0;
            }
        }
    }
    // if cl argument is invalid or not provided, tell the user
    printf("Usage: ./vigenere key_string\n");
    return 1;
}


char encrypt_text(string plain, int *key_int, int nk, char *cipher)
{
    int start;
    // counter for key
    int k = 0;
    
    // iterate over plain text
    for (int i = 0, np = strlen(plain); i < np; i++)
    {
        // check if element is alpha
        if (isalpha(plain[i]))
        {
            /*compute where ASCII alphabet starts,
            upper at 65, lower case at 97*/
            start = isupper(plain[i]) ? 65 : 97;
            int ki = k >= nk ? (k % nk) : k;
            /*pi - start + k = relative shift from starting letter,
            % ALPHABET = wrap around to the beginning of alphabet,
            + start = go from relative shift to absolute value for the ASCII letter
            get the matching index for key_int, handle np > nk, wrap around */
            cipher[i] = ((int) plain[i] - start + key_int[ki]) % ALPHABET + start;
            k++;
        }
        else
        {
            cipher[i] = plain[i];
        }
    }
    return 0;
}


int key_to_int(string k, int *key_int)
{
    for (int i = 0, nk = strlen(k); i < nk; i++)
    {
        // make letter uppercase, and subtract 65 so that A/a=0, ...
        key_int[i] = (int) toupper(k[i]) - 65;
    }
    return 0;
}


int all_alpha(string s)
{
    int only_alpha = 1;
    int current;
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        // 1 if s[i] isalpha() else 0
        current = isalpha(s[i]) ? 1 : 0;
        only_alpha = only_alpha && current;
    }
    return only_alpha;
}