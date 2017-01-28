/**
 * helpers.h
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n);
// search() itself calls recursive function binary_search()
bool binary_search(int array[], int start, int end, int value);

/**
 * Sorts array of n values.
 */
void sort(int values[], int n);
