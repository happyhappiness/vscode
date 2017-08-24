{
	pid_t child;
	int stdin_pipe[2], stdout_pipe[2], tmp;
#if HAVE_POSIX_SPAWNP
	posix_spawn_file_actions_t actions;
	int r;
#endif
	struct archive_cmdline *cmdline;

	cmdline = __archive_cmdline_allocate();
	if (cmdline == NULL)
		goto state_allocated;
	if (__archive_cmdline_parse(cmdline, cmd) != ARCHIVE_OK)
		goto state_allocated;

	if (pipe(stdin_pipe) == -1)
		goto state_allocated;
	if (stdin_pipe[0] == 1 /* stdout */) {
		if ((tmp = dup(stdin_pipe[0])) == -1)
			goto stdin_opened;
		close(stdin_pipe[0]);
		stdin_pipe[0] = tmp;
	}
	if (pipe(stdout_pipe) == -1)
		goto stdin_opened;
	if (stdout_pipe[1] == 0 /* stdin */) {
		if ((tmp = dup(stdout_pipe[1])) == -1)
			goto stdout_opened;
		close(stdout_pipe[1]);
		stdout_pipe[1] = tmp;
	}

#if HAVE_POSIX_SPAWNP

	r = posix_spawn_file_actions_init(&actions);
	if (r != 0) {
		errno = r;
		goto stdout_opened;
	}
	r = posix_spawn_file_actions_addclose(&actions, stdin_pipe[1]);
	if (r != 0)
		goto actions_inited;
	r = posix_spawn_file_actions_addclose(&actions, stdout_pipe[0]);
	if (r != 0)
		goto actions_inited;
	/* Setup for stdin. */
	r = posix_spawn_file_actions_adddup2(&actions, stdin_pipe[0], 0);
	if (r != 0)
		goto actions_inited;
	if (stdin_pipe[0] != 0 /* stdin */) {
		r = posix_spawn_file_actions_addclose(&actions, stdin_pipe[0]);
		if (r != 0)
			goto actions_inited;
	}
	/* Setup for stdout. */
	r = posix_spawn_file_actions_adddup2(&actions, stdout_pipe[1], 1);
	if (r != 0)
		goto actions_inited;
	if (stdout_pipe[1] != 1 /* stdout */) {
		r = posix_spawn_file_actions_addclose(&actions, stdout_pipe[1]);
		if (r != 0)
			goto actions_inited;
	}
	r = posix_spawnp(&child, cmdline->path, &actions, NULL,
		cmdline->argv, NULL);
	if (r != 0)
		goto actions_inited;
	posix_spawn_file_actions_destroy(&actions);

#else /* HAVE_POSIX_SPAWNP */

#if HAVE_VFORK
	child = vfork();
#else
	child = fork();
#endif
	if (child == -1)
		goto stdout_opened;
	if (child == 0) {
		close(stdin_pipe[1]);
		close(stdout_pipe[0]);
		if (dup2(stdin_pipe[0], 0 /* stdin */) == -1)
			_exit(254);
		if (stdin_pipe[0] != 0 /* stdin */)
			close(stdin_pipe[0]);
		if (dup2(stdout_pipe[1], 1 /* stdout */) == -1)
			_exit(254);
		if (stdout_pipe[1] != 1 /* stdout */)
			close(stdout_pipe[1]);
		execvp(cmdline->path, cmdline->argv);
		_exit(254);
	}
#endif /* HAVE_POSIX_SPAWNP */

	close(stdin_pipe[0]);
	close(stdout_pipe[1]);

	*child_stdin = stdin_pipe[1];
	fcntl(*child_stdin, F_SETFL, O_NONBLOCK);
	*child_stdout = stdout_pipe[0];
	fcntl(*child_stdout, F_SETFL, O_NONBLOCK);
	__archive_cmdline_free(cmdline);

	return child;

#if HAVE_POSIX_SPAWNP
actions_inited:
	errno = r;
	posix_spawn_file_actions_destroy(&actions);
#endif
stdout_opened:
	close(stdout_pipe[0]);
	close(stdout_pipe[1]);
stdin_opened:
	close(stdin_pipe[0]);
	close(stdin_pipe[1]);
state_allocated:
	__archive_cmdline_free(cmdline);
	return -1;
}