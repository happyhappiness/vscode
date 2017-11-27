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
