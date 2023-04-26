#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "vector.h"
#include "banker.h"

// Checks if setup is sane, returns false if not
bool sanity_check(int NRES, int NPROC, int *available, int **max, int **allocation)
{
    // Check if any line in allocated exceeds available
    for (int i = 0; i < NPROC; i++)
    {
        if (compare_vectors(available, allocation[i], NRES) != -1)
        {
            // oh no, we're goin crazy!
            printf("Integrity test failed: allocated resources exceed total resources\n");
            return false;
        }
    }

    // Check if any line in allocated exceeds corrosponding line in max
    for (int i = 0; i < NPROC; i++)
    {
        int test = compare_vectors(max[i], allocation[i], NRES);
        // Test should be -1, if not we have a problem
        if (test != -1)
        {
            printf("Integrity test failed: allocated resources exceed demand for Thread %d\n", i);
            // Find how many we exceed by
            int error = max[i][test] - allocation[i][test];
            printf("Need %d instances of resource %d\n", error, test);
            return false;
        }
    }
    // Whew, we're in the clear
    return true;
}