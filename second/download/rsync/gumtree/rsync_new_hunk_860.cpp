			set_socket_options(f_in, sockopts);
		else
			set_socket_options(f_in, lp_socket_options());
		set_nonblocking(f_in);
	}

	if (exchange_protocols(f_in, f_out, line, sizeof line, 0) < 0)
		return -1;

	line[0] = 0;
	if (!read_line_old(f_in, line, sizeof line))
		return -1;

	if (!*line || strcmp(line, "#list") == 0) {
		rprintf(FLOG, "module-list request from %s (%s)\n",
			host, addr);
		send_listing(f_out);
