int main (int argc, char **argv)
{
	int    collectd_argc = 0;
	char  *collectd      = NULL;
	char **collectd_argv = NULL;

	struct sigaction sa;

	int i = 0;

	/* parse command line options */
	while (42) {
		int c = getopt (argc, argv, "hc:P:");

		if (-1 == c)
			break;

		switch (c) {
			case 'c':
				collectd = optarg;
				break;
			case 'P':
				pidfile = optarg;
				break;
			case 'h':
			default:
				exit_usage (argv[0]);
		}
	}

	for (i = optind; i < argc; ++i)
		if (0 == strcmp (argv[i], "-f"))
			break;

	/* i < argc => -f already present */
	collectd_argc = 1 + argc - optind + ((i < argc) ? 0 : 1);
	collectd_argv = (char **)calloc (collectd_argc + 1, sizeof (char *));

	if (NULL == collectd_argv) {
		fprintf (stderr, "Out of memory.");
		return 3;
	}

	collectd_argv[0] = (NULL == collectd) ? "collectd" : collectd;

	if (i == argc)
		collectd_argv[collectd_argc - 1] = "-f";

	for (i = optind; i < argc; ++i)
		collectd_argv[i - optind + 1] = argv[i];

	collectd_argv[collectd_argc] = NULL;

	openlog ("collectdmon", LOG_CONS | LOG_PID, LOG_DAEMON);

	if (-1 == daemonize ())
	{
		free (collectd_argv);
		return 1;
	}

	sa.sa_handler = sig_int_term_handler;
	sa.sa_flags   = 0;
	sigemptyset (&sa.sa_mask);

	if (0 != sigaction (SIGINT, &sa, NULL)) {
		syslog (LOG_ERR, "Error: sigaction() failed: %s", strerror (errno));
		free (collectd_argv);
		return 1;
	}

	if (0 != sigaction (SIGTERM, &sa, NULL)) {
		syslog (LOG_ERR, "Error: sigaction() failed: %s", strerror (errno));
		free (collectd_argv);
		return 1;
	}

	sa.sa_handler = sig_hup_handler;

	if (0 != sigaction (SIGHUP, &sa, NULL)) {
		syslog (LOG_ERR, "Error: sigaction() failed: %s", strerror (errno));
		free (collectd_argv);
		return 1;
	}

	while (0 == loop) {
		int status = 0;

		if (0 != collectd_start (collectd_argv)) {
			syslog (LOG_ERR, "Error: failed to start collectd.");
			break;
		}

		assert (0 < collectd_pid);
		while ((collectd_pid != waitpid (collectd_pid, &status, 0))
				&& (EINTR == errno))
			if ((0 != loop) || (0 != restart))
				collectd_stop ();

		collectd_pid = 0;

		log_status (status);
		check_respawn ();

		if (0 != restart) {
			syslog (LOG_INFO, "Info: restarting collectd");
			restart = 0;
		}
		else if (0 == loop)
			syslog (LOG_WARNING, "Warning: restarting collectd");
	}

	syslog (LOG_INFO, "Info: shutting down collectdmon");

	pidfile_delete ();
	closelog ();

	free (collectd_argv);
	return 0;
}