	char *sargs[MAX_ARGS];
	int sargc = 0;
	char line[MAXPATHLEN];
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
