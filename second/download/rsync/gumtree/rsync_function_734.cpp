int start_daemon(int f_in, int f_out)
{
	char line[200];
	char *motd;
	int i = -1;
	extern char *config_file;
	extern int am_server;

	if (!lp_load(config_file, 0)) {
		exit_cleanup(RERR_SYNTAX);
	}

	log_init();

	if (!am_server) {
		set_socket_options(f_in, "SO_KEEPALIVE");
		set_socket_options(f_in, lp_socket_options());
		set_nonblocking(f_in);
	}

	io_printf(f_out, "@RSYNCD: %d\n", PROTOCOL_VERSION);

	motd = lp_motd_file();
	if (motd && *motd) {
		FILE *f = fopen(motd,"r");
		while (f && !feof(f)) {
			int len = fread(line, 1, sizeof(line)-1, f);
			if (len > 0) {
				line[len] = 0;
				io_printf(f_out, "%s", line);
			}
		}
		if (f) fclose(f);
		io_printf(f_out, "\n");
	}

	if (!read_line(f_in, line, sizeof(line)-1)) {
		return -1;
	}

	if (sscanf(line,"@RSYNCD: %d", &remote_protocol) != 1) {
		io_printf(f_out, "@ERROR: protocol startup error\n");
		return -1;
	}
	if (protocol_version > remote_protocol)
		protocol_version = remote_protocol;

	while (i == -1) {
		line[0] = 0;
		if (!read_line(f_in, line, sizeof(line)-1)) {
			return -1;
		}

		if (!*line || strcmp(line,"#list")==0) {
			send_listing(f_out);
			return -1;
		}

		if (*line == '#') {
			/* it's some sort of command that I don't understand */
			io_printf(f_out, "@ERROR: Unknown command '%s'\n", line);
			return -1;
		}

		i = lp_number(line);
		if (i == -1) {
			io_printf(f_out, "@ERROR: Unknown module '%s'\n", line);
			return -1;
		}
	}

	return rsync_module(f_in, f_out, i);
}