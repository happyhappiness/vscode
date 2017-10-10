 		return;
 	skip_prefix(branch, "refs/heads/", &branch);
 	die(_("'%s' is already checked out at '%s'"),
 	    branch, wt->path);
 }
 
-int replace_each_worktree_head_symref(const char *oldref, const char *newref)
+int replace_each_worktree_head_symref(const char *oldref, const char *newref,
+				      const char *logmsg)
 {
 	int ret = 0;
 	struct worktree **worktrees = get_worktrees(0);
 	int i;
 
 	for (i = 0; worktrees[i]; i++) {
 		if (worktrees[i]->is_detached)
 			continue;
 		if (strcmp(oldref, worktrees[i]->head_ref))
 			continue;
 
 		if (set_worktree_head_symref(get_worktree_git_dir(worktrees[i]),
-					     newref)) {
+					     newref, logmsg)) {
 			ret = -1;
 			error(_("HEAD of working tree %s is not updated"),
 			      worktrees[i]->path);
 		}
 	}
 
