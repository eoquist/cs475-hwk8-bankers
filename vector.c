#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "vector.h"

// Creates and returns a new copy of the input matrix
int **deep_copy_matrix(int **matrix, int n, int m)
{
    // Allocate memory for the new matrix
    int **new_matrix = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
    {
        new_matrix[i] = (int *)malloc(m * sizeof(int));
    }
    // Copy the contents of the matrix to the new matrix
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            new_matrix[i][j] = matrix[i][j];
        }
    }
    return new_matrix;
}

// Adds two vectors of the same size
int *add_vectors(int *v1, int *v2, int size)
{
    // Allocate memory for new vector
    int *new_vector = malloc(size * sizeof(int));
    // Add vectors element wise
    for (int i = 0; i < size; i++)
    {
        new_vector[i] = v1[i] + v2[i];
    }
    return new_vector;
}

// Subtracts two vectors of the same size
int *subtract_vectors(int *v1, int *v2, int size)
{
    // Allocate memory for new vector
    int *new_vector = malloc(size * sizeof(int));
    // Add vectors element wise
    for (int i = 0; i < size; i++)
    {
        new_vector[i] = v1[i] - v2[i];
    }
    return new_vector;
}

// Adds two matrices of the same size
int **add_matrices(int **m1, int **m2, int n, int m)
{
    // Allocate memory for the new matrix
    int **new_matrix = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
    {
        new_matrix[i] = (int *)malloc(m * sizeof(int));
    }
    // Add matrices element wise
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            new_matrix[i][j] = m1[i][j] + m2[i][j];
        }
    }
    return new_matrix;
}

// Adds two matrices of the same size
int **subtract_matrices(int **m1, int **m2, int n, int m)
{
    // Allocate memory for the new matrix
    int **new_matrix = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
    {
        new_matrix[i] = (int *)malloc(m * sizeof(int));
    }
    // Subtract matrices element wise
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            new_matrix[i][j] = m1[i][j] - m2[i][j];
        }
    }
    return new_matrix;
}

// Compare two vectors of length n
// Returns -1 if v1 <= v2 element wise, false otherwise return index of greater elem
int compare_vectors(int *v1, int *v2, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (v1[i] < v2[i])
        {
            return i; // if any element in v1 is greater than the corresponding element in v2
        } 
    }
    return -1;
}

// Prints an input vector
void print_vector(int *vector, int size)
{
    // Print it
    for (int i = 0; i < size; i++)
    {
        printf("%d ", vector[i]);
    }
    printf("\n");
}

// Prints an input matrix
void print_matrix(int **matrix, int n, int m)
{
    // Print it
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// checks if a vector is either all zeros or ones - used for finish vector in bankers algorithm
bool is_zero_vector(int *finish, int n){
    bool is_zero = true;
    for(int i = 0; i < n; i++){
        is_zero = is_zero && (finish[i] == 0);
    }
    return is_zero;
}
bool is_ones_vector(int *finish, int n){
    bool is_one = true;
    for(int i = 0; i < n; i++){
        is_one = is_one && (finish[i] == 1);
    }
    return is_one;
}