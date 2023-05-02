// TODO: function prototypes of vector and matrix operations

// Vectors must be the same size
int *deep_copy_vector(int *vec, int size);
int *add_vectors(int *v1, int *v2, int size);
int *subtract_vectors(int *v1, int *v2, int size);
int compare_vectors(int *v1, int *v2, int size);
void print_vector(int *vector, int size);

// Matrices must be the same size
int **deep_copy_matrix(int **matrix, int n, int m);
int **add_matrices(int **m1, int **m2, int n, int m);
int **subtract_matrices(int **m1, int **m2, int n, int m);
void print_matrix(int **matrix, int n, int m);

// extra functions
bool is_zero_vector(int *finish, int n);
bool is_ones_vector(int *finish, int n);