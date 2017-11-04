static char *finish_pre_exec(pid_t pid, int fd, char *request,
			     int argc, char *argv[])
{
	int j, status = -1;

	if (request) {
		write_buf(fd, request, strlen(request)+1);
		for (j = 0; j < argc; j++)
			write_buf(fd, argv[j], strlen(argv[j])+1);
	}

	write_byte(fd, 0);

	close(fd);

	if (wait_process(pid, &status, 0) < 0
	 || !WIFEXITED(status) || WEXITSTATUS(status) != 0) {
		char *e;
		if (asprintf(&e, "pre-xfer exec returned failure (%d)\n", status) < 0)
			out_of_memory("finish_pre_exec");
		return e;
	}
	return NULL;
}