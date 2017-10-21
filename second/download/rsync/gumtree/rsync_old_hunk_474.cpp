	if (setuid(uid) || getuid() != uid) {
		rprintf(FERROR,"setuid %d failed\n", uid);
		io_printf(fd,"@ERROR: setuid failed\n");
		return -1;
	}

	io_printf(fd,"@RSYNCD: OK\n");

	argv[argc++] = "rsyncd";

	while (1) {
		if (!read_line(fd, line, sizeof(line)-1)) {
