
/* this is called when a connection is established to a client
   and we want to start talking. The setup of the system is done from
   here */
int start_daemon(int f_in, int f_out)
{
	char line[1024];
	char *motd;
	char *addr = client_addr(f_in);
	char *host = client_name(f_in);
	int i;

	rprintf(FLOG, "connect from %s (%s)\n", host, addr);

	io_set_sock_fds(f_in, f_out);

	if (!lp_load(config_file, 0))
		exit_cleanup(RERR_SYNTAX);

	log_init();

	if (!am_server) {
		set_socket_options(f_in, "SO_KEEPALIVE");
		if (sockopts)
			set_socket_options(f_in, sockopts);
		else
			set_socket_options(f_in, lp_socket_options());
		set_nonblocking(f_in);
	}

	io_printf(f_out, "@RSYNCD: %d\n", protocol_version);

	motd = lp_motd_file();
