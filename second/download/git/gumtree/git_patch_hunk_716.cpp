 			die("internal error: work tree has already been set\n"
 			    "Current worktree: %s\nNew worktree: %s",
 			    work_tree, new_work_tree);
 		return;
 	}
 	git_work_tree_initialized = 1;
-	work_tree = xstrdup(real_path(new_work_tree));
+	work_tree = real_pathdup(new_work_tree);
 }
 
 const char *get_git_work_tree(void)
 {
 	return work_tree;
 }
