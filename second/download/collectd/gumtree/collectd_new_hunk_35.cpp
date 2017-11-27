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
