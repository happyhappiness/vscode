 			 const char *new,
 			 unsigned flags)
 {
 	int ret = 0;
 	struct child_process cp = CHILD_PROCESS_INIT;
 	const struct submodule *sub;
+	int *error_code_ptr, error_code;
+
+	if (!is_submodule_active(the_repository, path))
+		return 0;
+
+	if (flags & SUBMODULE_MOVE_HEAD_FORCE)
+		/*
+		 * Pass non NULL pointer to is_submodule_populated_gently
+		 * to prevent die()-ing. We'll use connect_work_tree_and_git_dir
+		 * to fixup the submodule in the force case later.
+		 */
+		error_code_ptr = &error_code;
+	else
+		error_code_ptr = NULL;
+
+	if (old && !is_submodule_populated_gently(path, error_code_ptr))
+		return 0;
 
 	sub = submodule_from_path(null_sha1, path);
 
 	if (!sub)
 		die("BUG: could not get submodule information for '%s'", path);
 
