			rprintf(FINFO, "%s\n", line);
	}
	kluge_around_eof = 0;

	if (rl_nulls) {
		for (i = 0; i < sargc; i++) {
			write_sbuf(f_out, sargs[i]);
			write_byte(f_out, 0);
		}
		write_byte(f_out, 0);
	} else {
		for (i = 0; i < sargc; i++)
			io_printf(f_out, "%s\n", sargs[i]);
		write_sbuf(f_out, "\n");
	}

	if (protocol_version < 23) {
		if (protocol_version == 22 || !am_sender)
			io_start_multiplex_in();
	}

	free(modname);

	return 0;
}

static char *finish_pre_exec(pid_t pid, int fd, char *request,
			     int argc, char *argv[])
{
	int j, status = -1;

	if (!request)
		request = "(NONE)";

	write_buf(fd, request, strlen(request)+1);
	for (j = 0; j < argc; j++)
		write_buf(fd, argv[j], strlen(argv[j])+1);
	write_byte(fd, 0);

	close(fd);

	if (wait_process(pid, &status, 0) < 0
	 || !WIFEXITED(status) || WEXITSTATUS(status) != 0) {
