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


bool check_is_safe(int *work, int *finish, int **alloc, int **need, char *ouput_str, int NPROC, int NRES) {
    if (is_ones_vector(finish, NPROC)){
        printf("%s", ouput_str);
        return true;
    }
    else{
        bool return_bool = true;
        for(int i = 0; i < NPROC; i++){
            int need_leq_work = compare_vectors(work, need[i], NRES); 
            if(finish[i] == 0 && need_leq_work != -1){
                // Print formats
                char safe_thread_str[10] = ""; // initialize to empty string
                sprintf(safe_thread_str, "T%d\t", i); // format the string and save it to the character array
                strcat(ouput_str, safe_thread_str);
                work = add_vectors(work, alloc[i], NRES);
                finish[i] = 1;
                return_bool = return_bool && check_is_safe(work, finish, alloc, need, ouput_str, NPROC, NRES);
                // finish[i] = 0;
                
            }
        }
        return return_bool;
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