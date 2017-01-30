#include <stdio.h>
#include <cs50.h>

/**
 * the collatz conjecture applies to all pos ints,
 * and states that is always possible to get back to 1 by doing:
 * if n == 1, stop
 * else if n % 2 == 0, repeat on n/2
 * else if n % 2 != 0, repeat on 3n + 1
 * now write a function collatz(n) in a recursive fashion that
 * returns the steps it needed to go back to one
 */
 
int collatz(int n)
{
    // base case, terminating the recursion
    if (n == 1)
        return 0;
    // recursive cases, calling the function within itself again with
    // slightly different arguments
    else if ((n % 2) == 0)
        return 1 + collatz(n / 2);
    else
        return 1 + collatz(3 * n + 1);
}


int main(int argc, char *argv[])
{
    if (argc == 2)
    {
        int n = atoi(argv[1]);
        if (n > 0)
        {
            printf("The Collatz conjecture!\n");
            printf("From %i: %i step(s) to get back to 1.\n", n, collatz(n));
            return 0;
        }
        else
        {
            printf("n must be > 0!\n");
            return 1;
        }
    }
    else
    {
        printf("Usage: ./collatz n");
        return 1;
    }
}