/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{ 
    if (n < 0)
    {
        return false;
    }
    int start = 0;
    int end = n - 1;
    return binary_search(values, start, end, value);
}


/**
 * binary search algorithm
 * 1. half (sub)array, (start + end)/2, int truncates the result. we could also round but truncation does the job too
 * 2. is the element the one we want?
 *      yes: return true
 *      no: is the element < or > than array[n/2]
 *          if <, search left half of array
 *          if >, search right half of array 
 * 3. go to step 1 but now with new start or end points
 *      left:now stretch of array we look for element is 0 to n/2 - 1
 *      right: now stretch of array we look for element is n/2 + 1 to n
 */
bool binary_search(int array[], int start, int end, int value)
{
    // make sure start is not larger than end, that would mean the element is not in the array
    if (start <= end)
    {
        int mid = (start + end) / 2;
        int mid_val = array[mid];
        // check if mid element is the element were looking for, if yes return true
        // if not the element we are looking for, keep on splitting the array and searching for array
        if (mid_val != value)
        {
            /**
             * compute new start and end
             * if value < mid_val, start = start, end = mid - 1
             * if value > mid_val, start = mid + 1, end = end
             */
            start = value < mid_val ? start : mid + 1;
            end = value < mid_val ? mid - 1 : end;
            binary_search(array, start, end, value);
        }
        return true;
    }
    return false; 
}


/**
 * Sorts array of n values.
 * implement an O(n) sorting algorithm
 * which is counting sort:
 * make key_array representing all possible ints
 * key_array[0 ... 65536] = 0
 * iterate over values, get value and increment key_array[value] by 1
 * iterate over key_array and put back sorted elements into values
 */
void sort(int values[], int n)
{
    // key array for each possible element in values, initialized with zeros
    int key_array[65537] = {0};
    // now iterate over values
    for (int i = 0; i < n; i++)
    {
        /* increment element in key_array at index = values[i] by one
        eg value[i] = 3, then key_array[3] + 1 */
        key_array[values[i]] += 1;
    }
    // now take the key_array and put the elements back into values in sorted order
    int k, v, i;
    for (k = 0, v = 0; v < n; k++)
    {
        if (key_array[k] > 0)
        {
            for (i = 0; i < key_array[k]; i++, v++)
            {
                values[v] = k;
            }
        }
    }
    return;
}