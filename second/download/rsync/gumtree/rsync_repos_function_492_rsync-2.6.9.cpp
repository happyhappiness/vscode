void
run_program(char **command)
{
    int pipe_fds[2], ret;
    pid_t pid;

    if (pipe(pipe_fds) < 0) {
	fprintf(stderr, "pipe failed: %s\n", strerror(errno));
	exit(1);
    }

    if ((pid = fork()) < 0) {
	fprintf(stderr, "fork failed: %s\n", strerror(errno));
	exit(1);
    }

    if (pid == 0) {
	if (save_data_from_program)
	    ret = dup2(pipe_fds[1], STDOUT_FILENO);
	else
	    ret = dup2(pipe_fds[0], STDIN_FILENO);
	if (ret < 0) {
	    fprintf(stderr, "Failed to dup (in child): %s\n", strerror(errno));
	    exit(1);
	}
	close(pipe_fds[0]);
	close(pipe_fds[1]);
	set_blocking(STDIN_FILENO);
	set_blocking(STDOUT_FILENO);
	execvp(command[0], command);
	fprintf(stderr, "Failed to exec %s: %s\n", command[0], strerror(errno));
	exit(1);
    }

    if (save_data_from_program)
	ret = dup2(pipe_fds[0], STDIN_FILENO);
    else
	ret = dup2(pipe_fds[1], STDOUT_FILENO);
    if (ret < 0) {
	fprintf(stderr, "Failed to dup (in parent): %s\n", strerror(errno));
	exit(1);
    }
    close(pipe_fds[0]);
    close(pipe_fds[1]);
}