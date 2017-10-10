 	trace_argv_printf(cmd->argv, "trace: run_command:");
 	fflush(NULL);
 
 #ifndef GIT_WINDOWS_NATIVE
 {
 	int notify_pipe[2];
+	int null_fd = -1;
+	char **childenv;
+	struct argv_array argv = ARGV_ARRAY_INIT;
+	struct child_err cerr;
+	struct atfork_state as;
+
 	if (pipe(notify_pipe))
 		notify_pipe[0] = notify_pipe[1] = -1;
 
+	if (cmd->no_stdin || cmd->no_stdout || cmd->no_stderr) {
+		null_fd = open("/dev/null", O_RDWR | O_CLOEXEC);
+		if (null_fd < 0)
+			die_errno(_("open /dev/null failed"));
+		set_cloexec(null_fd);
+	}
+
+	prepare_cmd(&argv, cmd);
+	childenv = prep_childenv(cmd->env);
+	atfork_prepare(&as);
+
+	/*
+	 * NOTE: In order to prevent deadlocking when using threads special
+	 * care should be taken with the function calls made in between the
+	 * fork() and exec() calls.  No calls should be made to functions which
+	 * require acquiring a lock (e.g. malloc) as the lock could have been
+	 * held by another thread at the time of forking, causing the lock to
+	 * never be released in the child process.  This means only
+	 * Async-Signal-Safe functions are permitted in the child.
+	 */
 	cmd->pid = fork();
 	failed_errno = errno;
 	if (!cmd->pid) {
+		int sig;
 		/*
-		 * Redirect the channel to write syscall error messages to
-		 * before redirecting the process's stderr so that all die()
-		 * in subsequent call paths use the parent's stderr.
+		 * Ensure the default die/error/warn routines do not get
+		 * called, they can take stdio locks and malloc.
 		 */
-		if (cmd->no_stderr || need_err) {
-			int child_err = dup(2);
-			set_cloexec(child_err);
-			set_error_handle(fdopen(child_err, "w"));
-		}
+		set_die_routine(child_die_fn);
+		set_error_routine(child_error_fn);
+		set_warn_routine(child_warn_fn);
 
 		close(notify_pipe[0]);
 		set_cloexec(notify_pipe[1]);
 		child_notifier = notify_pipe[1];
-		atexit(notify_parent);
 
 		if (cmd->no_stdin)
-			dup_devnull(0);
+			child_dup2(null_fd, 0);
 		else if (need_in) {
-			dup2(fdin[0], 0);
-			close_pair(fdin);
+			child_dup2(fdin[0], 0);
+			child_close_pair(fdin);
 		} else if (cmd->in) {
-			dup2(cmd->in, 0);
-			close(cmd->in);
+			child_dup2(cmd->in, 0);
+			child_close(cmd->in);
 		}
 
 		if (cmd->no_stderr)
-			dup_devnull(2);
+			child_dup2(null_fd, 2);
 		else if (need_err) {
-			dup2(fderr[1], 2);
-			close_pair(fderr);
+			child_dup2(fderr[1], 2);
+			child_close_pair(fderr);
 		} else if (cmd->err > 1) {
-			dup2(cmd->err, 2);
-			close(cmd->err);
+			child_dup2(cmd->err, 2);
+			child_close(cmd->err);
 		}
 
 		if (cmd->no_stdout)
-			dup_devnull(1);
+			child_dup2(null_fd, 1);
 		else if (cmd->stdout_to_stderr)
-			dup2(2, 1);
+			child_dup2(2, 1);
 		else if (need_out) {
-			dup2(fdout[1], 1);
-			close_pair(fdout);
+			child_dup2(fdout[1], 1);
+			child_close_pair(fdout);
 		} else if (cmd->out > 1) {
-			dup2(cmd->out, 1);
-			close(cmd->out);
+			child_dup2(cmd->out, 1);
+			child_close(cmd->out);
 		}
 
 		if (cmd->dir && chdir(cmd->dir))
-			die_errno("exec '%s': cd to '%s' failed", cmd->argv[0],
-			    cmd->dir);
-		if (cmd->env) {
-			for (; *cmd->env; cmd->env++) {
-				if (strchr(*cmd->env, '='))
-					putenv((char *)*cmd->env);
-				else
-					unsetenv(*cmd->env);
-			}
-		}
-		if (cmd->git_cmd)
-			execv_git_cmd(cmd->argv);
-		else if (cmd->use_shell)
-			execv_shell_cmd(cmd->argv);
-		else
-			sane_execvp(cmd->argv[0], (char *const*) cmd->argv);
+			child_die(CHILD_ERR_CHDIR);
+
+		/*
+		 * restore default signal handlers here, in case
+		 * we catch a signal right before execve below
+		 */
+		for (sig = 1; sig < NSIG; sig++) {
+			/* ignored signals get reset to SIG_DFL on execve */
+			if (signal(sig, SIG_DFL) == SIG_IGN)
+				signal(sig, SIG_IGN);
+		}
+
+		if (sigprocmask(SIG_SETMASK, &as.old, NULL) != 0)
+			child_die(CHILD_ERR_SIGPROCMASK);
+
+		/*
+		 * Attempt to exec using the command and arguments starting at
+		 * argv.argv[1].  argv.argv[0] contains SHELL_PATH which will
+		 * be used in the event exec failed with ENOEXEC at which point
+		 * we will try to interpret the command using 'sh'.
+		 */
+		execve(argv.argv[1], (char *const *) argv.argv + 1,
+		       (char *const *) childenv);
+		if (errno == ENOEXEC)
+			execve(argv.argv[0], (char *const *) argv.argv,
+			       (char *const *) childenv);
+
 		if (errno == ENOENT) {
-			if (!cmd->silent_exec_failure)
-				error("cannot run %s: %s", cmd->argv[0],
-					strerror(ENOENT));
-			exit(127);
+			if (cmd->silent_exec_failure)
+				child_die(CHILD_ERR_SILENT);
+			child_die(CHILD_ERR_ENOENT);
 		} else {
-			die_errno("cannot exec '%s'", cmd->argv[0]);
+			child_die(CHILD_ERR_ERRNO);
 		}
 	}
+	atfork_parent(&as);
 	if (cmd->pid < 0)
 		error_errno("cannot fork() for %s", cmd->argv[0]);
 	else if (cmd->clean_on_exit)
 		mark_child_for_cleanup(cmd->pid, cmd);
 
 	/*
-	 * Wait for child's execvp. If the execvp succeeds (or if fork()
+	 * Wait for child's exec. If the exec succeeds (or if fork()
 	 * failed), EOF is seen immediately by the parent. Otherwise, the
-	 * child process sends a single byte.
+	 * child process sends a child_err struct.
 	 * Note that use of this infrastructure is completely advisory,
 	 * therefore, we keep error checks minimal.
 	 */
 	close(notify_pipe[1]);
-	if (read(notify_pipe[0], &notify_pipe[1], 1) == 1) {
+	if (xread(notify_pipe[0], &cerr, sizeof(cerr)) == sizeof(cerr)) {
 		/*
-		 * At this point we know that fork() succeeded, but execvp()
+		 * At this point we know that fork() succeeded, but exec()
 		 * failed. Errors have been reported to our stderr.
 		 */
 		wait_or_whine(cmd->pid, cmd->argv[0], 0);
+		child_err_spew(cmd, &cerr);
 		failed_errno = errno;
 		cmd->pid = -1;
 	}
 	close(notify_pipe[0]);
+
+	if (null_fd >= 0)
+		close(null_fd);
+	argv_array_clear(&argv);
+	free(childenv);
 }
 #else
 {
 	int fhin = 0, fhout = 1, fherr = 2;
 	const char **sargv = cmd->argv;
 	struct argv_array nargv = ARGV_ARRAY_INIT;
