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
		if (!read_line(f_in, line, sizeof line - 1)) {
			rprintf(FERROR, "rsync: didn't get server startup line\n");
			return -1;
		}
