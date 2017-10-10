 {
 	if (check_repository_format_gently(gitdir, nongit_ok))
 		return NULL;
 
 	/* --work-tree is set without --git-dir; use discovered one */
 	if (getenv(GIT_WORK_TREE_ENVIRONMENT) || git_work_tree_cfg) {
+		char *to_free = NULL;
+		const char *ret;
+
 		if (offset != cwd->len && !is_absolute_path(gitdir))
-			gitdir = real_pathdup(gitdir, 1);
+			gitdir = to_free = real_pathdup(gitdir, 1);
 		if (chdir(cwd->buf))
 			die_errno("Could not come back to cwd");
-		return setup_explicit_git_dir(gitdir, cwd, nongit_ok);
+		ret = setup_explicit_git_dir(gitdir, cwd, nongit_ok);
+		free(to_free);
+		return ret;
 	}
 
 	/* #16.2, #17.2, #20.2, #21.2, #24, #25, #28, #29 (see t1510) */
 	if (is_bare_repository_cfg > 0) {
 		set_git_dir(offset == cwd->len ? gitdir : real_path(gitdir));
 		if (chdir(cwd->buf))
