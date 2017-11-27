	char    recvline[1024];
	char   *tokptr;
	char   *key;
	double  value;

	static int sockfd   = -1;
	static unsigned int complain = 0;

#if APCMAIN
# define PRINT_VALUE(name, val) printf("  Found property: name = %s; value = %f;\n", name, val)
#else
# define PRINT_VALUE(name, val) /**/
#endif

	if (sockfd < 0)
	{
		if ((sockfd = net_open (host, NULL, port)) < 0)
		{
			/* Complain once every six hours. */
			int complain_step = 21600 / atoi (COLLECTD_STEP);

			if ((complain % complain_step) == 0)
				syslog (LOG_ERR, "apcups plugin: Connecting to the apcupsd failed.");
			complain++;

			return (-1);
		}
		else if (complain > 1)
		{
			syslog (LOG_NOTICE, "apcups plugin: Connection re-established to the apcupsd.");
			complain = 0;
		}
	}

	if (net_send (&sockfd, "status", 6) < 0)
	{
		syslog (LOG_ERR, "apcups plugin: Writing to the socket failed.");
