		return -1;
	}

	if (!user) user = getenv("USER");
	if (!user) user = getenv("LOGNAME");

	/* set daemon_over_rsh to false since we need to build the 
	   true set of args passed through the rsh/ssh connection; 
	   this is a no-op for direct-socket-connection mode */
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

	if (sscanf(line,"@RSYNCD: %d", &remote_version) != 1) {
		/* note that read_line strips of \n or \r */
		rprintf(FERROR, "rsync: server sent \"%s\" rather than greeting\n",
			line);
		return -1;
	}

	p = strchr(path,'/');
	if (p) *p = 0;
	io_printf(f_out, "%s\n", path);
	if (p) *p = '/';

	/* Old servers may just drop the connection here,
	 rather than sending a proper EXIT command.  Yuck. */
	kludge_around_eof = list_only && (remote_version < 25);

	while (1) {
		if (!read_line(f_in, line, sizeof(line)-1)) {
			rprintf(FERROR, "rsync: didn't get server startup line\n");
			return -1;
		}
