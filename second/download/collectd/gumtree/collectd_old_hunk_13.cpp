static int apc_query_server (char *host, int port,
		struct apc_detail_s *apcups_detail)
{
	int     n;
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
		return (-1);
	}

	while ((n = net_recv (&sockfd, recvline, sizeof (recvline) - 1)) > 0)
	{
		assert (n < sizeof (recvline));
		recvline[n] = '\0';
#if APCMAIN
		printf ("net_recv = `%s';\n", recvline);
#endif /* if APCMAIN */

		tokptr = strtok (recvline, " :\t");
		while (tokptr != NULL)
		{
			key = tokptr;
			if ((tokptr = strtok (NULL, " :\t")) == NULL)
				continue;
			value = atof (tokptr);

			PRINT_VALUE (key, value);

			if (strcmp ("LINEV", key) == 0)
