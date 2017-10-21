
	if (path && *path)
		sargs[sargc++] = path;

	sargs[sargc] = NULL;

	io_printf(f_out, "@RSYNCD: %d\n", PROTOCOL_VERSION);

	if (!read_line(f_in, line, sizeof(line)-1)) {
		rprintf(FERROR, "rsync: did not see server greeting\n");
		return -1;
	}

