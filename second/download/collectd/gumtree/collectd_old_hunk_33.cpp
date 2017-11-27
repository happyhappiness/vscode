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
