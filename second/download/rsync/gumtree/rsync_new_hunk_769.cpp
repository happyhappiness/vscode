			line);
		return -1;
	}
	if (protocol_version > remote_protocol)
		protocol_version = remote_protocol;

	if (list_only && protocol_version >= 29)
		list_only |= 2;

	/* set daemon_over_rsh to false since we need to build the
	 * true set of args passed through the rsh/ssh connection;
	 * this is a no-op for direct-socket-connection mode */
	daemon_over_rsh = 0;
	server_options(sargs, &sargc);

	sargs[sargc++] = ".";

	if (path && *path)
		sargs[sargc++] = path;

	sargs[sargc] = NULL;

	if (verbose > 1)
		print_child_argv(sargs);

	p = strchr(path,'/');
	if (p) *p = 0;
	io_printf(f_out, "%s\n", path);
	if (p) *p = '/';

	/* Old servers may just drop the connection here,
	 rather than sending a proper EXIT command.  Yuck. */
	kluge_around_eof = list_only && protocol_version < 25 ? 1 : 0;

	while (1) {
		if (!read_line(f_in, line, sizeof line - 1)) {
			rprintf(FERROR, "rsync: didn't get server startup line\n");
			return -1;
		}
