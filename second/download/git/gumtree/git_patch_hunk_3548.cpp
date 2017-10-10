 		done_alias = 1;
 	}
 
 	return done_alias;
 }
 
-/*
- * Many parts of Git have subprograms communicate via pipe, expect the
- * upstream of a pipe to die with SIGPIPE when the downstream of a
- * pipe does not need to read all that is written.  Some third-party
- * programs that ignore or block SIGPIPE for their own reason forget
- * to restore SIGPIPE handling to the default before spawning Git and
- * break this carefully orchestrated machinery.
- *
- * Restore the way SIGPIPE is handled to default, which is what we
- * expect.
- */
-static void restore_sigpipe_to_default(void)
+int cmd_main(int argc, const char **argv)
 {
-	sigset_t unblock;
-
-	sigemptyset(&unblock);
-	sigaddset(&unblock, SIGPIPE);
-	sigprocmask(SIG_UNBLOCK, &unblock, NULL);
-	signal(SIGPIPE, SIG_DFL);
-}
-
-int main(int argc, char **av)
-{
-	const char **argv = (const char **) av;
 	const char *cmd;
 	int done_help = 0;
 
-	cmd = git_extract_argv0_path(argv[0]);
+	cmd = argv[0];
 	if (!cmd)
 		cmd = "git-help";
 
-	/*
-	 * Always open file descriptors 0/1/2 to avoid clobbering files
-	 * in die().  It also avoids messing up when the pipes are dup'ed
-	 * onto stdin/stdout/stderr in the child processes we spawn.
-	 */
-	sanitize_stdfds();
-
-	restore_sigpipe_to_default();
-
-	git_setup_gettext();
-
 	trace_command_performance(argv);
 
 	/*
 	 * "git-xxxx" is the same as "git xxxx", but we obviously:
 	 *
 	 *  - cannot take flags in between the "git" and the "xxxx".
