static int sock_exec(const char *prog)
{
	pid_t pid;
	int fd[2];

	if (socketpair_tcp(fd) != 0) {
		rsyserr(FERROR, errno, "socketpair_tcp failed");
		return -1;
	}
	if (DEBUG_GTE(CMD, 1))
		rprintf(FINFO, "Running socket program: \"%s\"\n", prog);

	pid = fork();
	if (pid < 0) {
		rsyserr(FERROR, errno, "fork");
		exit_cleanup(RERR_IPC);
	}

	if (pid == 0) {
		close(fd[0]);
		if (dup2(fd[1], STDIN_FILENO) < 0
		 || dup2(fd[1], STDOUT_FILENO) < 0) {
			fprintf(stderr, "Failed to run \"%s\"\n", prog);
			exit(1);
		}
		exit(system(prog));
	}

	close(fd[1]);
	return fd[0];
}