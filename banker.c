#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
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

//bool works(permutation, int *available, int **alloc, int **need, int NPROC, int NRES){
//return if this permutation works

//}


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
    // char safe_status[6] = "SAFE:\t";
    while (all_compatible) {
        all_compatible = is_zero_vector(finish, NPROC);
        for(int i = 0; i < NPROC; i++){
            int need_leq_work = compare_vectors(work, need[i], NRES); 
            if(finish[i] == 0 && need_leq_work != -1){
            // Print formats
            // char safe_thread_str[10] = ""; // initialize to empty string
            // sprintf(safe_thread_str, "T%d\t", i); // format the string and save it to the character array
            // strcat(safe_status, safe_thread_str);

                add_vectors(work, alloc[i], NRES);
                finish[i] = 1;
            }
        }
    }
    

    // there's an execution order in which all threads
    // ???
    print_vector(finish, NPROC);

	if (is_ones_vector(finish, NPROC)){
        // printf("%s", safe_status);
        // free everything
        free(finish);
        finish = NULL;
        free(work);
        work = NULL;
        return true; // safe
    } else{
        // free everything
        free(finish);
        finish = NULL;
        free(work);
        work = NULL;
        return false; // unsafe
    }
}

// test print
// printf("need:\n");
// print_matrix(need, NPROC, NRES);
// printf("need[%d] <= work ??\n", i);
// printf("need: ");
// print_vector(need[i],NRES);
// printf("work: ");
// print_vector(work,NRES);
// printf("compare vec value: %d\n", need_leq_work);