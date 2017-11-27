int main (int argc, char **argv)
{
	struct sigaction sigIntAction;
	struct sigaction sigTermAction;
	char *datadir    = PKGLOCALSTATEDIR;
	char *configfile = CONFIGFILE;
#if COLLECT_DAEMON
	struct sigaction sigChldAction;
	char *pidfile    = NULL;
	pid_t pid;
	int daemonize    = 1;
#endif
#if COLLECT_DEBUG
	char *logfile    = LOGFILE;
#endif

#if HAVE_LIBRRD
	operating_mode = MODE_LOCAL;
#else
	operating_mode = MODE_CLIENT;
#endif

	/* open syslog */
	openlog (PACKAGE, LOG_CONS | LOG_PID, LOG_DAEMON);

	/* read options */
	while (1)
	{
		int c;

		c = getopt (argc, argv, "hC:"
#if COLLECT_DAEMON
				"fP:"
#endif
		);

		if (c == -1)
			break;

		switch (c)
		{
			case 'C':
				configfile = optarg;
				break;
#if COLLECT_DAEMON
			case 'P':
				pidfile = optarg;
				break;
			case 'f':
				daemonize = 0;
				break;
#endif /* COLLECT_DAEMON */
			case 'h':
			default:
				exit_usage (argv[0]);
		} /* switch (c) */
	} /* while (1) */

#if COLLECT_DEBUG
	if ((logfile = cf_get_option ("LogFile", LOGFILE)) != NULL)
		DBG_STARTFILE (logfile, "Debug file opened.");
#endif

	/*
	 * Read options from the config file, the environment and the command
	 * line (in that order, with later options overwriting previous ones in
	 * general).
	 * Also, this will automatically load modules.
	 */
	if (cf_read (configfile))
	{
		fprintf (stderr, "Error: Reading the config file failed!\n"
				"Read the syslog for details.\n");
		return (1);
	}

	/*
	 * Change directory. We do this _after_ reading the config and loading
	 * modules to relative paths work as expected.
	 */
	if ((datadir = cf_get_option ("DataDir", PKGLOCALSTATEDIR)) == NULL)
	{
		fprintf (stderr, "Don't have a datadir to use. This should not happen. Ever.");
		return (1);
	}
	if (change_basedir (datadir))
	{
		fprintf (stderr, "Error: Unable to change to directory `%s'.\n", datadir);
		return (1);
	}

#if COLLECT_DAEMON
	/*
	 * fork off child
	 */
	sigChldAction.sa_handler = SIG_IGN;
	sigaction (SIGCHLD, &sigChldAction, NULL);

	if ((pidfile == NULL)
			&& ((pidfile = cf_get_option ("PIDFile", PIDFILE)) == NULL))
	{
		fprintf (stderr, "Cannot obtain pidfile. This shoud not happen. Ever.");
		return (1);
	}

	if (daemonize)
	{
		if ((pid = fork ()) == -1)
		{
			/* error */
			fprintf (stderr, "fork: %s", strerror (errno));
			return (1);
		}
		else if (pid != 0)
		{
			/* parent */
			/* printf ("Running (PID %i)\n", pid); */
			return (0);
		}

		/* Detach from session */
		setsid ();

		/* Write pidfile */
		if (pidfile_create (pidfile))
			exit (2);

		/* close standard descriptors */
		close (2);
		close (1);
		close (0);

		if (open ("/dev/null", O_RDWR) != 0)
		{
			syslog (LOG_ERR, "Error: Could not connect `STDIN' to `/dev/null'");
			return (1);
		}
		if (dup (0) != 1)
		{
			syslog (LOG_ERR, "Error: Could not connect `STDOUT' to `/dev/null'");
			return (1);
		}
		if (dup (0) != 2)
		{
			syslog (LOG_ERR, "Error: Could not connect `STDERR' to `/dev/null'");
			return (1);
		}
	} /* if (daemonize) */
#endif /* COLLECT_DAEMON */

	/*
	 * install signal handlers
	 */
	sigIntAction.sa_handler = sigIntHandler;
	sigaction (SIGINT, &sigIntAction, NULL);

	sigTermAction.sa_handler = sigTermHandler;
	sigaction (SIGTERM, &sigTermAction, NULL);

	/*
	 * run the actual loops
	 */
#if HAVE_LIBRRD
	if (operating_mode == MODE_SERVER)
		start_server ();
	else /* if (operating_mode == MODE_CLIENT || operating_mode == MODE_LOCAL || operating_mode == MODE_LOG) */
#endif
		start_client ();

	plugin_shutdown_all ();

#if COLLECT_DEBUG
	if (logfile != NULL)
		DBG_STOPFILE("debug file closed.");
#endif

	/* close syslog */
	syslog (LOG_INFO, "Exiting normally");
	closelog ();

#if COLLECT_DAEMON
	if (daemonize)
		pidfile_remove (pidfile);
#endif /* COLLECT_DAEMON */

	return (0);
}