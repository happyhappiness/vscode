static char *finish_pre_exec(pid_t pid, int fd, char *request,
			     char **early_argv, char **argv)
{
	int j = 0, status = -1;

	if (!request)
		request = "(NONE)";

	write_buf(fd, request, strlen(request)+1);
	if (early_argv) {
		for ( ; *early_argv; early_argv++)
			write_buf(fd, *early_argv, strlen(*early_argv)+1);
		j = 1; /* Skip arg0 name in argv. */
	}
	for ( ; argv[j]; j++) {
		write_buf(fd, argv[j], strlen(argv[j])+1);
		if (argv[j][0] == '.' && argv[j][1] == '\0')
			break;
	}
	write_byte(fd, 0);

	close(fd);

	if (wait_process(pid, &status, 0) < 0
	 || !WIFEXITED(status) || WEXITSTATUS(status) != 0) {
		char *e;
		if (asprintf(&e, "pre-xfer exec returned failure (%d)%s%s\n",
			     status, status < 0 ? ": " : "",
			     status < 0 ? strerror(errno) : "") < 0)
			out_of_memory("finish_pre_exec");
		return e;
	}
	return NULL;
}