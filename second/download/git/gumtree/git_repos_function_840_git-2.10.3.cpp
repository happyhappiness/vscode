int start_command(struct child_process *cmd)
{
	int need_in, need_out, need_err;
	int fdin[2], fdout[2], fderr[2];
	int failed_errno;
	char *str;

	if (!cmd->argv)
		cmd->argv = cmd->args.argv;
	if (!cmd->env)
		cmd->env = cmd->env_array.argv;

	/*
	 * In case of errors we must keep the promise to close FDs
	 * that have been passed in via ->in and ->out.
	 */

	need_in = !cmd->no_stdin && cmd->in < 0;
	if (need_in) {
		if (pipe(fdin) < 0) {
			failed_errno = errno;
			if (cmd->out > 0)
				close(cmd->out);
			str = "standard input";
			goto fail_pipe;
		}
		cmd->in = fdin[1];
	}

	need_out = !cmd->no_stdout
		&& !cmd->stdout_to_stderr
		&& cmd->out < 0;
	if (need_out) {
		if (pipe(fdout) < 0) {
			failed_errno = errno;
			if (need_in)
				close_pair(fdin);
			else if (cmd->in)
				close(cmd->in);
			str = "standard output";
			goto fail_pipe;
		}
		cmd->out = fdout[0];
	}

	need_err = !cmd->no_stderr && cmd->err < 0;
	if (need_err) {
		if (pipe(fderr) < 0) {
			failed_errno = errno;
			if (need_in)
				close_pair(fdin);
			else if (cmd->in)
				close(cmd->in);
			if (need_out)
				close_pair(fdout);
			else if (cmd->out)
				close(cmd->out);
			str = "standard error";
fail_pipe:
			error("cannot create %s pipe for %s: %s",
				str, cmd->argv[0], strerror(failed_errno));
			child_process_clear(cmd);
			errno = failed_errno;
			return -1;
		}
		cmd->err = fderr[0];
	}

	trace_argv_printf(cmd->argv, "trace: run_command:");
	fflush(NULL);

#ifndef GIT_WINDOWS_NATIVE
{
	int notify_pipe[2];
	if (pipe(notify_pipe))
		notify_pipe[0] = notify_pipe[1] = -1;

	cmd->pid = fork();
	failed_errno = errno;
	if (!cmd->pid) {
		/*
		 * Redirect the channel to write syscall error messages to
		 * before redirecting the process's stderr so that all die()
		 * in subsequent call paths use the parent's stderr.
		 */
		if (cmd->no_stderr || need_err) {
			int child_err = dup(2);
			set_cloexec(child_err);
			set_error_handle(fdopen(child_err, "w"));
		}

		close(notify_pipe[0]);
		set_cloexec(notify_pipe[1]);
		child_notifier = notify_pipe[1];
		atexit(notify_parent);

		if (cmd->no_stdin)
			dup_devnull(0);
		else if (need_in) {
			dup2(fdin[0], 0);
			close_pair(fdin);
		} else if (cmd->in) {
			dup2(cmd->in, 0);
			close(cmd->in);
		}

		if (cmd->no_stderr)
			dup_devnull(2);
		else if (need_err) {
			dup2(fderr[1], 2);
			close_pair(fderr);
		} else if (cmd->err > 1) {
			dup2(cmd->err, 2);
			close(cmd->err);
		}

		if (cmd->no_stdout)
			dup_devnull(1);
		else if (cmd->stdout_to_stderr)
			dup2(2, 1);
		else if (need_out) {
			dup2(fdout[1], 1);
			close_pair(fdout);
		} else if (cmd->out > 1) {
			dup2(cmd->out, 1);
			close(cmd->out);
		}

		if (cmd->dir && chdir(cmd->dir))
			die_errno("exec '%s': cd to '%s' failed", cmd->argv[0],
			    cmd->dir);
		if (cmd->env) {
			for (; *cmd->env; cmd->env++) {
				if (strchr(*cmd->env, '='))
					putenv((char *)*cmd->env);
				else
					unsetenv(*cmd->env);
			}
		}
		if (cmd->git_cmd)
			execv_git_cmd(cmd->argv);
		else if (cmd->use_shell)
			execv_shell_cmd(cmd->argv);
		else
			sane_execvp(cmd->argv[0], (char *const*) cmd->argv);
		if (errno == ENOENT) {
			if (!cmd->silent_exec_failure)
				error("cannot run %s: %s", cmd->argv[0],
					strerror(ENOENT));
			exit(127);
		} else {
			die_errno("cannot exec '%s'", cmd->argv[0]);
		}
	}
	if (cmd->pid < 0)
		error_errno("cannot fork() for %s", cmd->argv[0]);
	else if (cmd->clean_on_exit)
		mark_child_for_cleanup(cmd->pid);

	/*
	 * Wait for child's execvp. If the execvp succeeds (or if fork()
	 * failed), EOF is seen immediately by the parent. Otherwise, the
	 * child process sends a single byte.
	 * Note that use of this infrastructure is completely advisory,
	 * therefore, we keep error checks minimal.
	 */
	close(notify_pipe[1]);
	if (read(notify_pipe[0], &notify_pipe[1], 1) == 1) {
		/*
		 * At this point we know that fork() succeeded, but execvp()
		 * failed. Errors have been reported to our stderr.
		 */
		wait_or_whine(cmd->pid, cmd->argv[0], 0);
		failed_errno = errno;
		cmd->pid = -1;
	}
	close(notify_pipe[0]);
}
#else
{
	int fhin = 0