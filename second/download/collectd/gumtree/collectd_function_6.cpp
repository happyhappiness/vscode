int main (int argc, char **argv)
{
	struct sigaction sigIntAction, sigChldAction;
	pid_t pid;

	char *plugindir = NULL;
	char *basedir = "/var/lib/collectd";

	operating_mode = MODE_LOCAL;
	
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

		c = getopt (argc, argv, "cd:l"
#if COLLECT_PING
				"p:"
#endif /* COLLECT_PING */
				"P:sh");

		if (c == -1)
			break;

		switch (c)
		{
			case 'c':
				operating_mode = MODE_CLIENT;
				break;

			case 'd':
				basedir = optarg;
				break;

			case 'l':
				operating_mode = MODE_LOCAL;
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

			case 's':
				operating_mode = MODE_SERVER;
				break;

			case 'h':
			default:
				exit_usage (argv[0]);
		}
				
	}

	/*
	 * Load plugins and change to output directory
	 */
	if (plugin_load_all (plugindir) < 1)
	{
		fprintf (stderr, "Error: No plugins found.\n");
		return (1);
	}

	if (change_basedir (basedir))
	{
		fprintf (stderr, "Unable to change to directory `%s'.\n", basedir);
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
	if ((pid = fork ()) == -1)
	{
		/* error */
		syslog (LOG_ERR, "fork: %s", strerror (errno));
		return (1);
	}
	else if (pid != 0)
	{
		/* parent */
		/* printf ("Running (PID %i)\n", pid); */
		return (0);
	}
#endif
	
	/*
	 * run the actual loops
	 */
	if (operating_mode == MODE_SERVER)
		start_server ();
	else /* if (operating_mode == MODE_CLIENT || operating_mode == MODE_LOCAL) */
		start_client ();

	/*
	 * close syslog
	 */
	closelog ();

	return (0);
}