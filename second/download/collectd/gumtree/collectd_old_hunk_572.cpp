		return (0);

#if COLLECT_DAEMON
	/*
	 * fork off child
	 */
	memset (&sig_chld_action, '\0', sizeof (sig_chld_action));
	sig_chld_action.sa_handler = SIG_IGN;
	sigaction (SIGCHLD, &sig_chld_action, NULL);

    /*
     * Only daemonize if we're not being supervised
     * by upstart or systemd (when using Linux).
     */
	if (daemonize
#ifdef KERNEL_LINUX
	    && notify_upstart() == 0 && notify_systemd() == 0
#endif
	)
	{
		if ((pid = fork ()) == -1)
		{
			/* error */
			char errbuf[1024];
			fprintf (stderr, "fork: %s",
					sstrerror (errno, errbuf,
