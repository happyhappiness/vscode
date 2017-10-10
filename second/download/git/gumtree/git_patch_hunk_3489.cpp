 		/* Turn "git add pathspec..." to "git add -A pathspec..." */
 		addremove = 1;
 
 	if (!show_only && ignore_missing)
 		die(_("Option --ignore-missing can only be used together with --dry-run"));
 
+	if (!chmod_arg)
+		force_mode = 0;
+	else if (!strcmp(chmod_arg, "-x"))
+		force_mode = 0666;
+	else if (!strcmp(chmod_arg, "+x"))
+		force_mode = 0777;
+	else
+		die(_("--chmod param '%s' must be either -x or +x"), chmod_arg);
+
 	add_new_files = !take_worktree_changes && !refresh_only;
 	require_pathspec = !(take_worktree_changes || (0 < addremove_explicit));
 
 	hold_locked_index(&lock_file, 1);
 
 	flags = ((verbose ? ADD_CACHE_VERBOSE : 0) |
