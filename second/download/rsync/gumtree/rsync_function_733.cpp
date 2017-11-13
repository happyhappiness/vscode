int start_inband_exchange(char *user, char *path, int f_in, int f_out, int argc)
{
	int i;
	char *sargs[MAX_ARGS];
	int sargc = 0;
	char line[MAXPATHLEN];
	char *p;
	extern int kludge_around_eof;
	extern int am_sender;
	extern int daemon_over_rsh;
	extern int list_only;

	if (argc == 0 && !am_sender)
		list_only = 1;

	if (*path == '/') {
		rprintf(FERROR, "ERROR: The remote path must start with a module name\n");
		return -1;
	}

	if (!user) user = getenv("USER");
	if (!user) user = getenv("LOGNAME");

	/* set daemon_over_rsh to false since we need to build the
	 * true set of args passed through the rsh/ssh connection;
	 * this is a no-op for direct-socket-connection mode */
	daemon_over_rsh = 0;
	server_options(sargs, &sargc);

	sargs[sargc++] = ".";

	if (path && *path)
		sargs[sargc++] = path;

	sargs[sargc] = NULL;

	io_printf(f_out, "@RSYNCD: %d\n", PROTOCOL_VERSION);

	if (!read_line(f_in, line, sizeof(line)-1)) {
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

	p = strchr(path,'/');
	if (p) *p = 0;
	io_printf(f_out, "%s\n", path);
	if (p) *p = '/';

	/* Old servers may just drop the connection here,
	 rather than sending a proper EXIT command.  Yuck. */
	kludge_around_eof = list_only && (protocol_version < 25);

	while (1) {
		if (!read_line(f_in, line, sizeof(line)-1)) {
			rprintf(FERROR, "rsync: didn't get server startup line\n");
			return -1;
		}

		if (strncmp(line,"@RSYNCD: AUTHREQD ",18) == 0) {
			auth_client(f_out, user, line+18);
			continue;
		}

		if (strcmp(line,"@RSYNCD: OK") == 0) break;

		if (strcmp(line,"@RSYNCD: EXIT") == 0) {
			/* This is sent by recent versions of the
			 * server to terminate the listing of modules.
			 * We don't want to go on and transfer
			 * anything; just exit. */
			exit(0);
		}

		if (strncmp(line, "@ERROR", 6) == 0) {
			rprintf(FERROR,"%s\n", line);
			/* This is always fatal; the server will now
			 * close the socket. */
			return RERR_STARTCLIENT;
		} else {
			rprintf(FINFO,"%s\n", line);
		}
	}
	kludge_around_eof = False;

	for (i = 0; i < sargc; i++) {
		io_printf(f_out, "%s\n", sargs[i]);
	}
	io_printf(f_out, "\n");

	if (protocol_version < 23) {
		if (protocol_version == 22 || (protocol_version > 17 && !am_sender))
			io_start_multiplex_in(f_in);
	}

	return 0;
}