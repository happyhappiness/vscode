	char    recvline[1024];
	char   *tokptr;
	char   *key;
	double  value;

	static int sockfd   = -1;
	static complain_t compl;

#if APCMAIN
# define PRINT_VALUE(name, val) printf("  Found property: name = %s; value = %f;\n", name, val)
#else
# define PRINT_VALUE(name, val) /**/
#endif

	if (sockfd < 0)
	{
		if ((sockfd = net_open (host, NULL, port)) < 0)
		{
			plugin_complain (LOG_ERR, &compl, "apcups plugin: "
					"Connecting to the apcupsd failed.");
			return (-1);
		}
		else
		{
			plugin_relief (LOG_NOTICE, &compl, "apcups plugin: "
					"Connection re-established to the apcupsd.");
		}
	}

	if (net_send (&sockfd, "status", 6) < 0)
	{
		syslog (LOG_ERR, "apcups plugin: Writing to the socket failed.");
