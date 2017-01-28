/**
 * fifteen.c
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
// tells the compiler to include additional functions from the XOPEN and Posix standards
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);


int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE *file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = get_int();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(50000);
        }

        // sleep thread for animation's sake
        usleep(50000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}


/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    // ANSI escape sequence for erasing screen
    printf("\033[2J");
    // sequence for moving cursor to row, column 0,0
    printf("\033[%d;%dH", 0, 0);
}


/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}


/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
    /**
     * fill the 2D array board with integers
     * descending order from left to right and from top to bottom
     * NOTE: if d % 2 = 0, then swap 2 and 1 (d = 4: 3-1-2-0 instead of d = 3: 2-1-0)
     */
    
    // iterate across rows
    for (int r = 0, i = 1; r < d; r++)
    {
        // iterate over columns
        for (int c = 0; c < d; c++, i++)
        {
            board[r][c] = d * d - i;
        }
    }
    
    // swap 1 and 2 if d is even
    if (d % 2 == 0)
    {
        int temp = board[d - 1][d - 2];
        board[d - 1][d - 2] = board[d - 1][d - 3];
        board[d - 1][d - 3] = temp;
    }
}


/**
 * Prints the board in its current state.
 */
void draw(void)
{
    // the current num on the board
    int num;
    // iterate over rows
    for (int r = 0; r < d; r++)
    {
        // iterate over cols
        for (int c = 0; c < d; c++)
        {
            num = board[r][c];
            if (num < 10 && (d * d - 1) > 10)
            {
                // printf leading space if two-digit nums are on the board
                printf(" ");
            }
            
            if (num == 0)
            {
                printf("_ ");
            }
            else
            {
                printf("%i ", num);
            }
        }
        printf("\n\n");
    }
}


/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    /**
     * basic rules for moves:
     * - tile can only move up, left, down, right
     * - one of these adjacent tiles must be a zero
     * - important: board array of size [MAXDIM][MAXDIM]:
     * so elements larger than current board size are alse zero,
     * check for that
     * - if move legal, swap zero tile and selected tile, return true
     * - if illegal, return false
     */
    
    // first get index of tile to move
    int tr, tc;
    bool stop = false;
    for (int r = 0; r < d && !stop; r++)
    {
        for (int c = 0; c < d && !stop; c++)
        {
            if (board[r][c] == tile)
            {
                tr = r;
                tc = c;
                stop = true;
            }
        }
    }
    
    // ensure zero tile is adjacent to the moving tile
    // ensure no diagonal moves are considered legal
    int zr, zc;
    bool legal = false;
    for (int i = tr - 1; i < tr + 2 && !legal; i++)
    {
        for (int j = tc - 1; j < tc + 2 && !legal; j++)
        {
            // ensure neighbor index is in bounds of board, and no diagonals
            if (i > -1 && j > -1 && i < d && j < d && abs((tr + tc) - (i + j)) == 1)
            {
                if (board[i][j] == 0)
                {
                    legal = true;
                    zr = i;
                    zc = j;
                }
            }
        }
    }
    
    
    if (legal)
    {
        // save tile to move in tmp
        int tmp = board[tr][tc];
        board[tr][tc] = board[zr][zc];
        board[zr][zc] = tmp;
    }
    
    return legal;
}


/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    // iterate across rows and check if numbers are perfectly ordered
    int win = 0;
    for (int r = 0, i = 1; r < d; r++)
    {
        // iterate over columns
        for (int c = 0; c < d; c++, i++)
        {
            if (board[r][c] == i)
            {
                win += 1;
            }
        }
    }
    
    // ensure the bottom, right tile is zero
    if (board[d-1][d-1] == 0)
    {
        win += 1;
    }
    
    return win == d * d;
}
