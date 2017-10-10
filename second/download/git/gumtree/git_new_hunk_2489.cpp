
/*
 * Read branch description
 */
extern int read_branch_desc(struct strbuf *, const char *branch_name);

/*
 * Check if a branch is checked out in the main worktree or any linked
 * worktree and die (with a message describing its checkout location) if
 * it is.
 */
extern void die_if_checked_out(const char *branch);

/*
 * Check if a per-worktree symref points to a ref in the main worktree
 * or any linked worktree, and return the path to the exising worktree
 * if it is.  Returns NULL if there is no existing ref.  The caller is
 * responsible for freeing the returned path.
 */
extern char *find_shared_symref(const char *symref, const char *target);

#endif
