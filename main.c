#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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


  // need matrix ??? !!!
  //====================
  //====================
  //====================
  //====================


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

  // print everything
  // printf("resources: %d\n", NRES);
  // printf("processes: %d\n\navailable:\n", NPROC);
  print_vector(available, NRES);
  // printf("\nmax:\n");
  // print_matrix(max, NPROC, NRES);
  // printf("\nalloc:\n");
  // print_matrix(allocation, NPROC, NRES);

  // run sanity check
  if (!sanity_check(NRES, NPROC, available, max, allocation))
  {
    return -1;
  }

  // TODO: Run banker's safety algorithm
  // MAX VS NEED
  bool is_safe = isSafe(available,allocation,max,NRES,NPROC);
  printf("[%d] <-- 0 unsafe, 1 safe\n", is_safe);

  return 0;
}