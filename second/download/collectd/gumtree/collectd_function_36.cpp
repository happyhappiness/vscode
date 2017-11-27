int main (int argc, char **argv)
{
	struct sigaction sigIntAction, sigChldAction;
	pid_t pid;

	char *plugindir = NULL;
	char *basedir = "/var/lib/collectd";

	int daemonize = 1;

#ifdef HAVE_LIBRRD
	operating_mode = MODE_LOCAL;
#endif
	
	/*
	 * open syslog
	 */
	openlog (PACKAGE, LOG_CONS | LOG_PID, LOG_DAEMON);

	/*
	 * read options
	 */
	while (1)
	{
		int c;

		c = getopt (argc, argv, "d:fP:h"
#if HAVE_LIBRRD
				"csl"
#endif /* HAVE_LIBRRD */
#if COLLECT_PING
				"p:"
#endif /* COLLECT_PING */
		);

		if (c == -1)
			break;

		switch (c)
		{
#ifdef HAVE_LIBRRD
			case 'c':
				operating_mode = MODE_CLIENT;
				break;

			case 's':
				operating_mode = MODE_SERVER;
				break;

			case 'l':
				operating_mode = MODE_LOCAL;
				break;
#endif /* HAVE_LIBRRD */
			case 'd':
				basedir = optarg;
				break;
			case 'f':
				daemonize = 0;
				break;
#if COLLECT_PING
			case 'p':
				if (num_pinghosts < MAX_PINGHOSTS)
					pinghosts[num_pinghosts++] = optarg;
				else
					fprintf (stderr, "Maximum of %i ping hosts reached.\n", MAX_PINGHOSTS);
				break;
#endif /* COLLECT_PING */
			case 'P':
				plugindir = optarg;
				break;

			case 'h':
			default:
				exit_usage (argv[0]);
		}
				
	}

	/*
	 * Load plugins and change to output directory
	 * Loading plugins is done first so relative paths work as expected..
	 */
	if (plugin_load_all (plugindir) < 1)
	{
		fprintf (stderr, "Error: No plugins found.\n");
		return (1);
	}

	if (change_basedir (basedir))
	{
		fprintf (stderr, "Error: Unable to change to directory `%s'.\n", basedir);
		return (1);
	}

	/*
	 * install signal handlers
	 */
	sigIntAction.sa_handler = sigIntHandler;
	sigaction (SIGINT, &sigIntAction, NULL);

	sigChldAction.sa_handler = SIG_IGN;
	sigaction (SIGCHLD, &sigChldAction, NULL);

	/*
	 * fork off child
	 */
#if DEBUG == 0
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
		if (pidfile_create ())
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
#endif

	/*
	 * run the actual loops
	 */
#ifdef HAVE_LIBRRD
	if (operating_mode == MODE_SERVER)
		start_server ();
	else /* if (operating_mode == MODE_CLIENT || operating_mode == MODE_LOCAL) */
#endif
		start_client ();

	/*
	 * close syslog
	 */
	syslog (LOG_INFO, "Exiting normally");
	closelog ();

	if (daemonize)
		pidfile_remove();

	return (0);
}