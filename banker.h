/* declarations related to banker's algorithm */
bool sanity_check(int NRES, int NPROC, int *available, int **max, int **allocation);
bool is_terminal(int *finish);
bool check_is_safe(int *work, int *finish, int **alloc, int **need, char *ouput_str, int NPROC, int NRES);