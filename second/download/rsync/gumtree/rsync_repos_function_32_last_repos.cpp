int daemon_main(void)
{
	if (is_a_socket(STDIN_FILENO)) {
		int i;

		/* we are running via inetd - close off stdout and
		 * stderr so that library functions (and getopt) don't
		 * try to use them. Redirect them to /dev/null */
		for (i = 1; i < 3; i++) {
			close(i);
			open("/dev/null", O_RDWR);
		}

		return start_daemon(STDIN_FILENO, STDIN_FILENO);
	}

	if (!load_config(1)) {
		fprintf(stderr, "Failed to parse config file: %s\n", config_file);
		exit_cleanup(RERR_SYNTAX);
	}
	set_dparams(0);

	if (no_detach)
		create_pid_file();
	else
		become_daemon();

	if (rsync_port == 0 && (rsync_port = lp_rsync_port()) == 0)
		rsync_port = RSYNC_PORT;
	if (bind_address == NULL && *lp_bind_address())
		bind_address = lp_bind_address();

	log_init(0);

	rprintf(FLOG, "rsyncd version %s starting, listening on port %d\n",
		RSYNC_VERSION, rsync_port);
	/* TODO: If listening on a particular address, then show that
	 * address too.  In fact, why not just do getnameinfo on the
	 * local address??? */

	start_accept_loop(rsync_port, start_daemon);
	return -1;
}