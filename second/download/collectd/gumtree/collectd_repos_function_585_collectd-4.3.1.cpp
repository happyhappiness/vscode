int main (int argc, char **argv)
{
	struct sigaction sigIntAction;
	struct sigaction sigTermAction;
	char *configfile = CONFIGFILE;
	int test_config  = 0;
	const char *basedir;
#if COLLECT_DAEMON
	struct sigaction sigChldAction;
	pid_t pid;
	int daemonize    = 1;
#endif

	/* read options */
	while (1)
	{
		int c;

		c = getopt (argc, argv, "htC:"
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
			case 't':
				test_config = 1;
				break;
#if COLLECT_DAEMON
			case 'P':
				global_option_set ("PIDFile", optarg);
				break;
			case 'f':
				daemonize = 0;
				break;
#endif /* COLLECT_DAEMON */
			case 'h':
			default:
				exit_usage ();
		} /* switch (c) */
	} /* while (1) */

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
	if ((basedir = global_option_get ("BaseDir")) == NULL)
	{
		fprintf (stderr, "Don't have a basedir to use. This should not happen. Ever.");
		return (1);
	}
	else if (change_basedir (basedir))
	{
		fprintf (stderr, "Error: Unable to change to directory `%s'.\n", basedir);
		return (1);
	}

	/*
	 * Set global variables or, if that failes, exit. We cannot run with
	 * them being uninitialized. If nothing is configured, then defaults
	 * are being used. So this means that the user has actually done
	 * something wrong.
	 */
	if (init_global_variables () != 0)
		return (1);

	if (test_config)
		return (0);

#if COLLECT_DAEMON
	/*
	 * fork off child
	 */
	memset (&sigChldAction, '\0', sizeof (sigChldAction));
	sigChldAction.sa_handler = SIG_IGN;
	sigaction (SIGCHLD, &sigChldAction, NULL);

	if (daemonize)
	{
		if ((pid = fork ()) == -1)
		{
			/* error */
			char errbuf[1024];
			fprintf (stderr, "fork: %s",
					sstrerror (errno, errbuf,
						sizeof (errbuf)));
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
			ERROR ("Error: Could not connect `STDIN' to `/dev/null'");
			return (1);
		}
		if (dup (0) != 1)
		{
			ERROR ("Error: Could not connect `STDOUT' to `/dev/null'");
			return (1);
		}
		if (dup (0) != 2)
		{
			ERROR ("Error: Could not connect `STDERR' to `/dev/null'");
			return (1);
		}
	} /* if (daemonize) */
#endif /* COLLECT_DAEMON */

	/*
	 * install signal handlers
	 */
	memset (&sigIntAction, '\0', sizeof (sigIntAction));
	sigIntAction.sa_handler = sigIntHandler;
	sigaction (SIGINT, &sigIntAction, NULL);

	memset (&sigTermAction, '\0', sizeof (sigTermAction));
	sigTermAction.sa_handler = sigTermHandler;
	sigaction (SIGTERM, &sigTermAction, NULL);

	/*
	 * run the actual loops
	 */
	do_init ();
	do_loop ();

	/* close syslog */
	INFO ("Exiting normally");

	do_shutdown ();

#if COLLECT_DAEMON
	if (daemonize)
		pidfile_remove ();
#endif /* COLLECT_DAEMON */

	return (0);
}