int main (int argc, char **argv)
{
	int sleepingtime;
	struct sigaction sigIntAction, sigChldAction;
	pid_t pid;
	
	memset (basedir, '\0', PATH_MAX);
	
	openlog (PACKAGE, LOG_CONS | LOG_PID, LOG_DAEMON);

	while (1)
	{
		int c;

		c = getopt (argc, argv, "d:"
#if COLLECT_PING
				"p:"
#endif /* COLLECT_PING */
				"h");

		if (c == -1)
			break;

		switch (c)
		{
			case 'd':
				if (change_basedir (optarg) != 0)
					exit (1);
				break;
#if COLLECT_PING
			case 'p':
				ping_add_host (optarg);
				break;
#endif /* COLLECT_PING */
			case 'h':
			default:
				exit_usage (argv[0]);
		}
				
	}

	if (basedir[0] == '\0')
		if (change_basedir ("/var/lib/collectd") != 0)
			exit (1);

#ifdef HAVE_LIBKSTAT
	kc = NULL;
	update_kstat ();
#endif

#ifdef HAVE_LIBSTATGRAB
	if (sg_init ())
	{
		syslog (LOG_ERR, "sg_init: %s", sg_str_error (sg_get_error ()));
		exit (2);
	}

	if (sg_drop_privileges ())
	{
		syslog (LOG_ERR, "sg_drop_privileges: %s", sg_str_error (sg_get_error ()));
		exit (2);
	}
#endif

	init_all ();

	sigIntAction.sa_handler = sigIntHandler;
	sigaction (SIGINT, &sigIntAction, NULL);

	sigChldAction.sa_handler = sigChldHandler;
	sigaction (SIGCHLD, &sigChldAction, NULL);

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

	/* child */
	while (loop == 0)
	{
#if DEBUG
		fputs ("Starting update\n", stdout);
#endif

#ifdef HAVE_LIBKSTAT
		update_kstat ();
#endif

#if COLLECT_CPU
		cpu_update ();
#endif
#if COLLECT_DISK
		diskstats_update ();
#endif
#if COLLECT_LOAD
		load_update ();
#endif
#if COLLECT_MEMORY
		mem_update ();
#endif
#if COLLECT_PING
		ping_update ();
#endif
#if COLLECT_SENSORS
		sensors_update ();
#endif
#if COLLECT_SWAP
		swap_update ();
#endif
#if COLLECT_TRAFFIC
		traffic_update ();
#endif

#if DEBUG
		fputs ("Sleeping for 10 seconds\n", stdout);
#endif
		sleepingtime = 10;
		while (sleepingtime != 0)
		{
			if (loop != 0)
				break;

			sleepingtime = sleep (sleepingtime);
		}
	}

	/* close syslog */
	closelog ();

	return (0);
}