			set_socket_options(f_in, sockopts);
		else
			set_socket_options(f_in, lp_socket_options());
		set_nonblocking(f_in);
	}

	io_printf(f_out, "@RSYNCD: %d\n", protocol_version);

	motd = lp_motd_file();
	if (motd && *motd) {
		FILE *f = fopen(motd,"r");
		while (f && !feof(f)) {
			int len = fread(line, 1, sizeof line - 1, f);
			if (len > 0) {
				line[len] = 0;
				io_printf(f_out, "%s", line);
			}
		}
		if (f)
			fclose(f);
		io_printf(f_out, "\n");
	}

	if (!read_line(f_in, line, sizeof line - 1))
		return -1;

	if (sscanf(line,"@RSYNCD: %d", &remote_protocol) != 1) {
		io_printf(f_out, "@ERROR: protocol startup error\n");
		return -1;
	}
	if (protocol_version > remote_protocol)
		protocol_version = remote_protocol;

	line[0] = 0;
	if (!read_line(f_in, line, sizeof line - 1))
		return -1;

	if (!*line || strcmp(line, "#list") == 0) {
		rprintf(FLOG, "module-list request from %s (%s)\n",
			host, addr);
		send_listing(f_out);
