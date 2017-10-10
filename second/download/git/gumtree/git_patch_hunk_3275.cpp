  * Check if a branch is checked out in the main worktree or any linked
  * worktree and die (with a message describing its checkout location) if
  * it is.
  */
 extern void die_if_checked_out(const char *branch);
 
+/*
+ * Update all per-worktree HEADs pointing at the old ref to point the new ref.
+ * This will be used when renaming a branch. Returns 0 if successful, non-zero
+ * otherwise.
+ */
+extern int replace_each_worktree_head_symref(const char *oldref, const char *newref);
+
 #endif
