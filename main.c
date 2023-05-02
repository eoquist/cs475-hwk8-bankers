#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "vector.h"
#include "banker.h"

int main(int argc, char *argv[])
{
  // check if enough args
  if (argc != 2)
  {
    printf("Error: invalid arguments");
    printf("arguments should follow  the form \"bankers <filename.txt>\"\n");
    return -1;
  }

  int NRES;         // number of resource types
  int NPROC;        // number of processes
  int *available;   // available number of each resource
  int **max;        // max number of each resource for each process
  int **allocation; // currently allocated resources for each process
  int **need; 

  // get file name
  char *file_name = argv[1];
  // open file
  FILE *file_stream;
  file_stream = fopen(file_name, "r");
  if (file_stream == NULL)
  {
    printf("Error: file not found\n");
    return -1;
  }
  // get num processes and resources
  fscanf(file_stream, "%d", &NRES);
  fscanf(file_stream, "%d", &NPROC);

  // allocate and get available resources
  available = malloc(NRES * sizeof(int));
  for (int i = 0; i < NRES; i++)
  {
    fscanf(file_stream, "%d", &available[i]);
  }
  // allocate and get max resource matrix
  max = (int **)malloc(NPROC * sizeof(int *));
  for (int i = 0; i < NPROC; i++)
  {
    max[i] = (int *)malloc(NRES * sizeof(int));
    for (int j = 0; j < NRES; j++)
    {
      fscanf(file_stream, "%d", &max[i][j]);
    }
  }
  // allocate and get allocation matrix
  allocation = (int **)malloc(NPROC * sizeof(int *));
  for (int i = 0; i < NPROC; i++)
  {
    allocation[i] = (int *)malloc(NRES * sizeof(int));
    for (int j = 0; j < NRES; j++)
    {
      fscanf(file_stream, "%d", &allocation[i][j]);
    }
  }
  // need matrix 
  // need = (int **)malloc(NPROC * sizeof(int *)); // turns out this was causing leaks -- makes sense
  need = subtract_matrices(max,allocation,NPROC,NRES);

  // print everything
  // printf("resources: %d\n", NRES);
  // printf("processes: %d\n\navailable:\n", NPROC);
  // print_vector(available, NRES);
  // printf("\nmax:\n");
  // print_matrix(max, NPROC, NRES);
  // printf("\nalloc:\n");
  // print_matrix(allocation, NPROC, NRES);
  // printf("\nneed:\n");
  // print_matrix(need, NPROC, NRES);

  // run sanity check
  if (!sanity_check(NRES, NPROC, available, max, allocation)){
    return -1;
  }


  // ----------------------------------------------------
  // Run banker's safety algorithm

  int *work = deep_copy_vector(available,NRES);
  for(int i = 0; i < NPROC; i++){
    subtract_vectors(work, allocation[i],NRES);
  }
  int *finish = malloc(NPROC * sizeof(int));
  for (int i = 0; i < NPROC; i++){
    finish[i] = 0;
  }

  // creating a proper buffer size for output_str
  int buffer_size = ((1 + 3 + 1 )*NPROC) + 1;
  char* output_str = (char*) malloc(buffer_size * sizeof(char));
  int* safe_permutations = malloc(NPROC * sizeof(int));
  int* unsafe_proc = deep_copy_vector(finish,NPROC);

  bool is_safe = check_is_safe(work,finish,allocation,need,safe_permutations,unsafe_proc,NPROC,NRES,0);

  if(is_safe == 0){
    printf("UNSAFE:\t");
    for(int i = 0; i < NPROC; i++){
      if(unsafe_proc[i] == 0){
        printf("T%u ",unsafe_proc[i]);
      }
    }
    printf("can't finish:\n");
  }
  
  
  // ----------------------------------------------------

  // free everything 
  free(output_str);
  output_str = NULL;
  free(safe_permutations);
  safe_permutations = NULL;
  free(available);
  available = NULL;
  // free max
  for (int i = 0; i < NPROC; i++)
  {
    free(max[i]);
    max[i] = NULL;
  }
  free(max);
  max = NULL;
  // free allocation
  for (int i = 0; i < NPROC; i++)
  {
    free(allocation[i]);
    allocation[i] = NULL;
  }
  free(allocation);
  allocation = NULL;
  // free need
  for (int i = 0; i < NPROC; i++)
  {
    free(need[i]);
    need[i] = NULL;
  }
  free(need);
  need = NULL;
  // free finish and work
  free(finish);
  finish = NULL;
  free(work);
  work = NULL;

  // close the file stream
  fclose(file_stream);
  return 0;
}