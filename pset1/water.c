#include <cs50.h>
#include <stdio.h>

int main(void)
{
    printf("Minutes: ");
    int min = get_int();
    printf("Bottles: %i\n", min * 12);
}