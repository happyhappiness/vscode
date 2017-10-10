 		show_progress = 0;
 
 	if (abort_current_merge) {
 		int nargc = 2;
 		const char *nargv[] = {"reset", "--merge", NULL};
 
+		if (orig_argc != 2)
+			usage_msg_opt(_("--abort expects no arguments"),
+			      builtin_merge_usage, builtin_merge_options);
+
 		if (!file_exists(git_path_merge_head()))
 			die(_("There is no merge to abort (MERGE_HEAD missing)."));
 
 		/* Invoke 'git reset --merge' */
 		ret = cmd_reset(nargc, nargv, prefix);
 		goto done;
 	}
 
+	if (continue_current_merge) {
+		int nargc = 1;
+		const char *nargv[] = {"commit", NULL};
+
+		if (orig_argc != 2)
+			usage_msg_opt(_("--continue expects no arguments"),
+			      builtin_merge_usage, builtin_merge_options);
+
+		if (!file_exists(git_path_merge_head()))
+			die(_("There is no merge in progress (MERGE_HEAD missing)."));
+
+		/* Invoke 'git commit' */
+		ret = cmd_commit(nargc, nargv, prefix);
+		goto done;
+	}
+
 	if (read_cache_unmerged())
 		die_resolve_conflict("merge");
 
 	if (file_exists(git_path_merge_head())) {
 		/*
 		 * There is no unmerged entry, don't advise 'git
