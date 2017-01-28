#define _XOPEN_SOURCE

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

// parameters for brute-force
static const char alphabet[] =
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

static const int alphabet_size = sizeof(alphabet) - 1;

// prototypes
bool crypt_cmp(char *word, char *hash, char* salt);
bool dict_attack(char *dict_loc, char *hash, char* salt);
bool brute_force(char * str, int index, int max_len, char *hash, char* salt);


int main(int argc, string argv[])
{
    char *method;
    char *hash;
    bool dict_att, brute_att;
    /* make sure exactly one or two command line argument were passed,
    firt element of argv[] is the script name itself */
    if (argc < 2)
    {
        printf("Usage: ./crack method hash\n");
        return 1;        
    }
    else if (argc == 2)
    {
        dict_att = true;
        brute_att = true;
        // the hash to be decrypted given by user
        hash = argv[1];
    }
    else if (argc == 3)
    {
        method = argv[1];
        if (strcmp(method, "-d") == 0)
        {
            dict_att = true;
        }
        else if (strcmp(method, "-b") == 0)
        {
            brute_att = true;
        }
        else
        {
            printf("Unknown flag:\n");
            printf("\t-d for dictionary attack\n\t-b for brute-force attack\n\tno flag will try both\n");
            return 1;
        }
        hash = argv[2];
    }

    // extract the salt from the hash, ie the first 2 alphanumericals
    char salt[3] = {hash[0], hash[1], 0};
    
    if (dict_att)
    {
        char *dict_loc = "words2.txt";
        if (dict_attack(dict_loc, salt, hash))
        {
            return 0;
        }
    }
    
    if (brute_att)
    {
        printf("Performing brute-force attack ...\n");
        const int max_len = 4;
        char * buf = malloc(max_len + 1);
        for (int i = 1; i <= max_len; ++i)
        {
            memset(buf, 0, max_len + 1);
            if (brute_force(buf, 0, i, hash, salt))
            {
                free(buf);
                return 0;
            }
        }
    }
    printf("Not able to crack hash!");
    return 1;
}


// takes a plaintext word, encrypts and compares to provided hash
bool crypt_cmp(char *word, char *hash, char* salt)
{
    return strcmp(crypt(word, salt), hash) == 0;
}


// performs dict attack
bool dict_attack(char *dict_loc, char *hash, char* salt)
{
    FILE *dict = fopen(dict_loc, "r");
    
    // ensure file was opened correctly
    if (dict == NULL)
    {
        printf("Error: could not open dict!");
        return false;
    }

    printf("Performing dictionary-attack ...\n");
    
    // initialize an empty buffer for fgets() to load a string in it
    const int buff_size = 24;
    char buff[buff_size];
    
    // read dict line by line
    while (fgets(buff, buff_size, dict))
    {
        /* only allow <= 4 letter words to save time,
        the 5th elemt is newline */
        if (strlen(buff) <= 5)
        {
            // we need to strip newline from end of buff
            buff[strcspn(buff, "\n")] = 0;
            if (crypt_cmp(buff, hash, salt))
            {
                printf("Success: %s\n", buff);
                return true;
            }
        }
    }
    
    printf("Dictionary-attack failed!");
    return false;
}

bool brute_force(char * str, int index, int max_len, char *hash, char* salt)
{
    for (int i = 0; i < alphabet_size; ++i)
    {
        str[index] = alphabet[i];

        if (index == max_len - 1)
        {
            if (crypt_cmp(str, hash, salt))
            {
                printf("Success: %s\n", str);
                return true;
            }
        }
        else
        {
            brute_force(str, index + 1, max_len, hash, salt);
        }
    }
    return false;
}