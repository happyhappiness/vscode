				     default_af_hint);
	if (fd == -1)
		exit_cleanup(RERR_SOCKETIO);

	set_socket_options(fd, sockopts);

	ret = start_inband_exchange(user, path, fd, fd, argc);

	return ret ? ret : client_run(fd, fd, -1, argc, argv);
}

int start_inband_exchange(char *user, char *path, int f_in, int f_out,
			  int argc)
{
	int i;
	char *sargs[MAX_ARGS];
	int sargc = 0;
	char line[BIGPATHBUFLEN];
	char *p;

	if (argc == 0 && !am_sender)
		list_only |= 1;

	if (*path == '/') {
		rprintf(FERROR,
			"ERROR: The remote path must start with a module name\n");
		return -1;
	}

	if (!user)
		user = getenv("USER");
	if (!user)
		user = getenv("LOGNAME");

	io_printf(f_out, "@RSYNCD: %d\n", protocol_version);

	if (!read_line(f_in, line, sizeof line - 1)) {
		rprintf(FERROR, "rsync: did not see server greeting\n");
		return -1;
	}

	if (sscanf(line,"@RSYNCD: %d", &remote_protocol) != 1) {
		/* note that read_line strips of \n or \r */
		rprintf(FERROR, "rsync: server sent \"%s\" rather than greeting\n",
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

		if (strncmp(line,"@RSYNCD: AUTHREQD ",18) == 0) {
			auth_client(f_out, user, line+18);
