 		return NULL;
 	}
 	else if (git_work_tree_cfg) { /* #6, #14 */
 		if (is_absolute_path(git_work_tree_cfg))
 			set_git_work_tree(git_work_tree_cfg);
 		else {
-			char core_worktree[PATH_MAX];
+			char *core_worktree;
 			if (chdir(gitdirenv))
 				die_errno("Could not chdir to '%s'", gitdirenv);
 			if (chdir(git_work_tree_cfg))
 				die_errno("Could not chdir to '%s'", git_work_tree_cfg);
-			if (!getcwd(core_worktree, PATH_MAX))
-				die_errno("Could not get directory '%s'", git_work_tree_cfg);
-			if (chdir(cwd))
+			core_worktree = xgetcwd();
+			if (chdir(cwd->buf))
 				die_errno("Could not come back to cwd");
 			set_git_work_tree(core_worktree);
+			free(core_worktree);
 		}
 	}
 	else if (!git_env_bool(GIT_IMPLICIT_WORK_TREE_ENVIRONMENT, 1)) {
 		/* #16d */
 		set_git_dir(gitdirenv);
 		free(gitfile);
