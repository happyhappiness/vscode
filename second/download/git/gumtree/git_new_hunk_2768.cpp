 * Check if a branch is checked out in the main worktree or any linked
 * worktree and die (with a message describing its checkout location) if
 * it is.
 */
extern void die_if_checked_out(const char *branch);

#endif
