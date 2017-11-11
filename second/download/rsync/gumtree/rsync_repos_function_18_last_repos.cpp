static char *finish_pre_exec(pid_t pid, int write_fd, int read_fd, char *request,
			     char **early_argv, char **argv)
{
	char buf[BIGPATHBUFLEN], *bp;
	int j = 0, status = -1, msglen = sizeof buf - 1;

	if (!request)
		request = "(NONE)";

	write_buf(write_fd, request, strlen(request)+1);
	if (early_argv) {
		for ( ; *early_argv; early_argv++)
			write_buf(write_fd, *early_argv, strlen(*early_argv)+1);
		j = 1; /* Skip arg0 name in argv. */
	}
	for ( ; argv[j]; j++)
		write_buf(write_fd, argv[j], strlen(argv[j])+1);
	write_byte(write_fd, 0);

	close(write_fd);

	/* Read the stdout from the pre-xfer exec program.  This it is only
	 * displayed to the user if the script also returns an error status. */
	for (bp = buf; msglen > 0; msglen -= j) {
		if ((j = read(read_fd, bp, msglen)) <= 0) {
			if (j == 0)
				break;
			if (errno == EINTR)
				continue;
			break; /* Just ignore the read error for now... */
		}
		bp += j;
		if (j > 1 && bp[-1] == '\n' && bp[-2] == '\r') {
			bp--;
			j--;
			bp[-1] = '\n';
		}
	}
	*bp = '\0';

	close(read_fd);

	if (wait_process(pid, &status, 0) < 0
	 || !WIFEXITED(status) || WEXITSTATUS(status) != 0) {
		char *e;
		if (asprintf(&e, "pre-xfer exec returned failure (%d)%s%s%s\n%s",
			     status, status < 0 ? ": " : "",
			     status < 0 ? strerror(errno) : "",
			     *buf ? ":" : "", buf) < 0)
			return "out_of_memory in finish_pre_exec\n";
		return e;
	}
	return NULL;
}