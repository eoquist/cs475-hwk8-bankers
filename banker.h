/* declarations related to banker's algorithm */
bool sanity_check(int NRES, int NPROC, int *available, int **max, int **allocation);
bool is_terminal(int *finish);
bool check_is_safe(int *work, int *finish, int **alloc, int **need, int *safe_permutations, int *unsafe_proc, int NPROC, int NRES, int seq_idx);