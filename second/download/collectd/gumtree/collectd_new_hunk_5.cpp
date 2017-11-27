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
