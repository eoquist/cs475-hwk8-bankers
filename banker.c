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


bool check_is_safe(int *work, int *finish, int **alloc, int **need, int *safe_permutations, int *unsafe_proc, int NPROC, int NRES, int seq_idx){
    bool safe = false;
    if (is_ones_vector(finish, NPROC)){
        printf("SAFE:\t");
        for(int i = 0; i < NPROC; i++){
            printf("T%u ",safe_permutations[i]);
        }
        printf("\n");
        return true;
    }
    else{
        for(int i = 0; i < NPROC; i++){
            int need_leq_work = compare_vectors(work, need[i], NRES); // -1 means more available than need
            if(need_leq_work != -1){
                // continue;
                printf("UNSAFE:\t");
                for(int i = 0; i < NPROC; i++){
                if(unsafe_proc[i] == 0){
                    printf("T%u ",unsafe_proc[i]);
                }
                }
                printf("can't finish:\n");
                break;
            }
            if(finish[i] == 1){
                continue;
            }
            int *safe_permutations_copy = deep_copy_vector(safe_permutations,NPROC); 
            int *finish_copy = deep_copy_vector(finish,NPROC); 
            int *work_copy = add_vectors(work, alloc[i], NRES);
           
            finish_copy[i] = 1;
            // need a way to track what sequence we're on -- aka depth
            safe_permutations_copy[seq_idx] = i;
            unsafe_proc[i] = 1;
            // printf("unsafe thread: T%u\n", unsafe_proc[i]);
            if(check_is_safe(work_copy, finish_copy, alloc, need, safe_permutations_copy, unsafe_proc, NPROC, NRES, seq_idx+1)){
                safe = true;
            }

            // free
            free(work_copy);
            work_copy = NULL;
            free(finish_copy);
            finish_copy = NULL;
            free(safe_permutations_copy);
            safe_permutations_copy = NULL;
        }
    }
    return safe;
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

// valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --show-reachable=yes ./bankers safe.txt 
// valgrind --leak-check=full ./bankers safe.txt 