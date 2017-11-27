	sigaction (SIGCHLD, &sigChldAction, NULL);

	/*
	 * fork off child
	 */
#if DEBUG == 0
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
	syslog (LOG_INFO, "Exiting normally");
	closelog ();

	return (0);
}
