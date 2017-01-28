#include <cs50.h>
#include <stdio.h>

void make_pyramids(int height);
void make_half_pyramid(int row, int height, char side);
void print_hashes(int n);
void print_spaces(int n);


int main(void)
{
    int height;
    
    do
    {
        printf("Height: ");
        height = get_int();
    }
    while (height < 0 || height > 23);
    
    make_pyramids(height);
}

void make_pyramids(int height)
{
    for (int row = 1; row <= height; row++)
    {
        //printf("%i\n", row);
        make_half_pyramid(row, height, 'l');
        print_spaces(2);
        make_half_pyramid(row, height, 'r');
    }

}

void make_half_pyramid(int row, int height, char side)
{
    int blanks = height - row;
    
    if (side == 'l')
    {
        print_spaces(blanks);
        print_hashes(row);
    }
    else
    {
        print_hashes(row);
        //print_spaces(blanks);
        printf("\n");
    }
}

void print_hashes(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("#");
    }
}

void print_spaces(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf(" ");
    }
}
