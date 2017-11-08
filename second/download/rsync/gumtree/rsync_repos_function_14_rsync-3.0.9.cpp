int start_daemon(int f_in, int f_out)
{
	char line[1024];
	char *addr, *host;
	int i;

	io_set_sock_fds(f_in, f_out);

	/* We must load the config file before calling any function that
	 * might cause log-file output to occur.  This ensures that the
	 * "log file" param gets honored for the 2 non-forked use-cases
	 * (when rsync is run by init and run by a remote shell). */
	if (!load_config(0))
		exit_cleanup(RERR_SYNTAX);

	addr = client_addr(f_in);
	host = client_name(f_in);
	rprintf(FLOG, "connect from %s (%s)\n", host, addr);

	if (!am_server) {
		set_socket_options(f_in, "SO_KEEPALIVE");
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
		return -1;
	}

	if (*line == '#') {
		/* it's some sort of command that I don't understand */
		io_printf(f_out, "@ERROR: Unknown command '%s'\n", line);
		return -1;
	}

	if ((i = lp_number(line)) < 0) {
		rprintf(FLOG, "unknown module '%s' tried from %s (%s)\n",
			line, host, addr);
		io_printf(f_out, "@ERROR: Unknown module '%s'\n", line);
		return -1;
	}

#ifdef HAVE_SIGACTION
	sigact.sa_flags = SA_NOCLDSTOP;
#endif
	SIGACTION(SIGCHLD, remember_children);

	return rsync_module(f_in, f_out, i, addr, host);
}