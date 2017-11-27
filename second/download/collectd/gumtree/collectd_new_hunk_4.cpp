void exit_usage (char *name)
{
	printf ("Usage: %s [OPTIONS]\n\n"
			
			"Available options:\n"
			"  General:\n"
			"    -c              Start in client (sender) mode\n"
			"    -d <dir>        Base directory to use. Default: /var/lib/collectd\n"
			"    -l              Start in local mode (no network)\n"
			"    -P <dir>        Set the plugin-directory\n"
			"    -s              Start in server (listener) mode\n"
#if COLLECT_PING
			"  Ping:\n"
			"    -p <host>       Host to ping periodically, may be repeated to ping\n"
			"                    more than one host.\n"
#endif /* COLLECT_PING */
			"\n%s %s, http://verplant.org/collectd/\n"
			"by Florian octo Forster <octo@verplant.org>\n",
			PACKAGE, PACKAGE, VERSION);
	exit (0);
}

int start_client (void)
{
	int sleepingtime;

#ifdef HAVE_LIBKSTAT
	kc = NULL;
	update_kstat ();
#endif

#ifdef HAVE_LIBSTATGRAB
	if (sg_init ())
	{
		syslog (LOG_ERR, "sg_init: %s", sg_str_error (sg_get_error ()));
		return (-1);
	}

	if (sg_drop_privileges ())
	{
		syslog (LOG_ERR, "sg_drop_privileges: %s", sg_str_error (sg_get_error ()));
		return (-1);
	}
#endif

	plugin_init_all ();

	while (loop == 0)
	{
		curtime = time (NULL);
#ifdef HAVE_LIBKSTAT
		update_kstat ();
#endif
		plugin_read_all ();

		sleepingtime = 10;
		while (sleepingtime != 0)
		{
			if (loop != 0)
				break;
			sleepingtime = sleep (sleepingtime);
		}
	}

	return (0);
}

int start_server (void)
{
	char *host;
	char *type;
	char *instance;
	char *values;

	while (loop == 0)
	{
		if (multicast_receive (&host, &type, &instance, &values) == 0)
			plugin_write (host, type, instance, values);

		if (host     != NULL) free (host);     host     = NULL;
		if (type     != NULL) free (type);     type     = NULL;
		if (instance != NULL) free (instance); instance = NULL;
		if (values   != NULL) free (values);   values   = NULL;
	}
	
	return (0);
}

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
