/**
 * generate.c
 *
 * Generates pseudorandom numbers in [0,MAX), one per line.
 *
 * Usage: generate n [s]
 *
 * where n is number of pseudorandom numbers to print
 * and s is an optional seed
 */
 
#define _XOPEN_SOURCE

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// upper limit on range of integers that can be generated
#define LIMIT 65536

int main(int argc, string argv[])
{
    // make sure that user provides either 2 or 3 cl arguments
    if (argc != 2 && argc != 3)
    {
        printf("Usage: ./generate n [s]\n");
        return 1;
    }

    // convert the cl argument from string to int
    int n = atoi(argv[1]);

    // if second cl argument: seed the random numgen with that number
    // if not provided, use the current time as seed
    if (argc == 3)
    {
        srand48((long) atoi(argv[2]));
    }
    else
    {
        // return a time_t object representing current time
        srand48((long) time(NULL));
    }

    // iterate over the desired num of random numbers,
    // generate one number and print it to stdout
    for (int i = 0; i < n; i++)
    {
        printf("%i\n", (int) (drand48() * LIMIT));
    }

    // success
    return 0;
}
