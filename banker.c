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

// bool isSafe(int *available, int **max, int **allocation, int NRES, int NPROC) {
//     bool found = true;
//     while (found) {
//         found = false;
//         for (int i = 0; i < NPROC; i++) {
//             if (Finish[i] == 0) {
//                 bool needs_met = true;
//                 for (int j = 0; j < NRES; j++) {
//                     if (max[i][j] - allocation[i][j] > Work[j]) {
//                         needs_met = false;
//                         break;
//                     }
//                 }
//                 if (needs_met) {
//                     found = true;
//                     for (int j = 0; j < NRES; j++) {
//                         Work[j] += allocation[i][j];
//                     }
//                     Finish[i] = 1;
//                 }
//             }
//         }
//     }

//     for (int i = 0; i < NPROC; i++) {
//         if (Finish[i] == 0) {
//             return false;
//         }
//     }
//     return true;
// }

// return permutations from another function

bool isSafe(int *available, int **alloc, int **need, int NRES, int NPROC) {
    /**
     * What is going on with David's pseudocode ????
    */

    // work[NRES] = available.clone();
    int *work_available = malloc(NRES * sizeof(int)); // printf("available vector size: %d\n", size);
    for (int i = 0; i < NRES; i++)
    {
        work_available[i] = available[i];
    }
    
	// finish[NPROC] = [0, 0, ..., 0] for all 0 <= i < NPROC
    int *finish = malloc(NPROC * sizeof(int));
    for (int i = 0; i < NPROC; i++) {
        finish[i] = 0;
    }

	// while (exists unfinished thread i && Need[i] <= work) {
	// 	// pretend that thread i finishes execution
	// 	// then OS can reclaim thread i's allocated resources
	// 	work += alloc[i]
	// 	finish[i] = 1
	// }
    // vvvvvvvvvvvvvvvvvvvvvvvvvvv
    // while theres still unfinished threads and 
    int *v1 = need[0]; // where [#] represents an unfinished thread i
    int *v2 = work_available;
    int comparison_value = compare_vectors(v1, v2, NRES); 
    // -1 if v1 >= v2 element wise, false otherwise return index of greater elem

	// there's an execution order in which all threads
    // ^^^^^^^ tf does this mean
	// if (finish == [1, 1, ..., 1])
	// 	return true	// safe!
	return false;		// unsafe
}

