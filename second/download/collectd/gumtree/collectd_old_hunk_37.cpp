
	/* read options */
	while (1)
	{
		int c;

		c = getopt (argc, argv, "C:P:M:D:fh"
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
			case 'C':
				configfile = optarg;
				break;
			case 'P':
				pidfile = optarg;
				break;
			case 'M':
				plugindir = optarg;
				break;
			case 'D':
				datadir = optarg;
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

	if (change_basedir (datadir))
	{
		fprintf (stderr, "Error: Unable to change to directory `%s'.\n", datadir);
		return (1);
	}

	/*
	 * fork off child
	 */
#if COLLECT_DAEMON
	sigChldAction.sa_handler = SIG_IGN;
	sigaction (SIGCHLD, &sigChldAction, NULL);

	if (daemonize)
	{
		if ((pid = fork ()) == -1)
		{
			/* error */
			fprintf (stderr, "fork: %s", strerror (errno));
