 {
 	int ret = 0;
 	struct worktree **worktrees = get_worktrees(0);
 	int i;
 
 	for (i = 0; worktrees[i]; i++) {
+		struct ref_store *refs;
+
 		if (worktrees[i]->is_detached)
 			continue;
-		if (strcmp(oldref, worktrees[i]->head_ref))
+		if (worktrees[i]->head_ref &&
+		    strcmp(oldref, worktrees[i]->head_ref))
 			continue;
 
-		if (set_worktree_head_symref(get_worktree_git_dir(worktrees[i]),
-					     newref, logmsg)) {
-			ret = -1;
-			error(_("HEAD of working tree %s is not updated"),
-			      worktrees[i]->path);
-		}
+		refs = get_worktree_ref_store(worktrees[i]);
+		if (refs_create_symref(refs, "HEAD", newref, logmsg))
+			ret = error(_("HEAD of working tree %s is not updated"),
+				    worktrees[i]->path);
 	}
 
 	free_worktrees(worktrees);
 	return ret;
 }
