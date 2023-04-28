/* declarations related to banker's algorithm */
bool sanity_check(int NRES, int NPROC, int *available, int **max, int **allocation);
bool isSafe(int *available, int **alloc, int **need, int NRES, int NPROC);