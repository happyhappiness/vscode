 	 * Always open file descriptors 0/1/2 to avoid clobbering files
 	 * in die().  It also avoids messing up when the pipes are dup'ed
 	 * onto stdin/stdout/stderr in the child processes we spawn.
 	 */
 	sanitize_stdfds();
 
+	restore_sigpipe_to_default();
+
 	git_setup_gettext();
 
 	trace_command_performance(argv);
 
 	/*
 	 * "git-xxxx" is the same as "git xxxx", but we obviously:
