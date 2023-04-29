// TODO: function prototypes of vector and matrix operations

// Creates and returns a new copy of the input matrix
int **deep_copy_matrix(int **matrix, int n, int m);

// Vectors must be the same size
int *add_vectors(int *v1, int *v2, int size);
int *subtract_vectors(int *v1, int *v2, int size);
int compare_vectors(int *v1, int *v2, int size);
void print_vector(int *vector, int size);
bool is_zero_vector(int *finish, int n);

// Matrices must be the same size
int **add_matrices(int **m1, int **m2, int n, int m);
int **subtract_matrices(int **m1, int **m2, int n, int m);
void print_matrix(int **matrix, int n, int m);