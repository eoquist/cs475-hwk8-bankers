// TODO: function prototypes of vector and matrix operations

// Creates and returns a new copy of the input matrix
int **deep_copy_matrix(int **matrix, int n, int m);

// Adds two vectors of the same size
int *add_vectors(int *v1, int *v2, int size);

// Subtracts two vectors of the same size
int *subtract_vectors(int *v1, int *v2, int size);

// Adds two matrices of the same size
int **add_matrices(int **m1, int **m2, int n, int m);

// Adds two matrices of the same size
int **subtract_matrices(int **m1, int **m2, int n, int m);

// Compare two vectors of length n
// Returns -1 if v1 >= v2 element wise, false otherwise return index of greater elem
int compare_vectors(int *v1, int *v2, int size);

// Prints an input vector
void print_vector(int *vector, int size);

// Prints an input matrix
void print_matrix(int **matrix, int n, int m);