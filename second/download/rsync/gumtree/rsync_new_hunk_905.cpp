			rprintf(FINFO, "%s\n", line);
	}
	kluge_around_eof = 0;

	if (rl_nulls) {
		for (i = 0; i < sargc; i++) {
			if (!sargs[i]) /* stop at --protect-args NULL */
				break;
			write_sbuf(f_out, sargs[i]);
			write_byte(f_out, 0);
		}
		write_byte(f_out, 0);
	} else {
		for (i = 0; i < sargc; i++)
			io_printf(f_out, "%s\n", sargs[i]);
		write_sbuf(f_out, "\n");
	}

	if (protect_args)
		send_protected_args(f_out, sargs);

	if (protocol_version < 23) {
		if (protocol_version == 22 || !am_sender)
			io_start_multiplex_in();
	}

	free(modname);

	return 0;
}

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
