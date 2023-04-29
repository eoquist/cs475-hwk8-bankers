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




// return permutations from another function ???

bool isSafe(int *available, int **alloc, int **need, int NPROC, int NRES) {
    int *work = malloc(NRES * sizeof(int));
    for (int i = 0; i < NRES; i++){
        work[i] = available[i];
    }
    int *finish = malloc(NPROC * sizeof(int));
    for (int i = 0; i < NPROC; i++) {
        finish[i] = 0;
    }

    bool all_compatible = true;
    while (all_compatible) {
        all_compatible = is_zero_vector(finish, NPROC);
        for(int i = 0; i < NPROC; i++){
            // test print
            // printf("need:\n");
            // print_matrix(need, NPROC, NRES);
            int need_leq_work = compare_vectors(need[i], work, NRES); // -1 if v1 >= v2 element wise, false otherwise return index of greater elem
            // printf("need[%d] <= work\n", i);
            // if(i == 0){
            //     printf("work:\n");
            //     print_vector(work,NRES);
            //     printf("compare vec value: %d\n", need_leq_work);
            //     exit(1);
            // }
            
            
            if(finish[i] == 0 && need_leq_work != -1){
                add_vectors(work, alloc[i], NRES);
                finish[i] = 1;
            }
        }
        printf("all compatible? = %d\n", all_compatible);
    }
    
    // free everything
    free(finish);
    finish = NULL;
    free(work);
    work = NULL;

	return false;		// unsafe
}

