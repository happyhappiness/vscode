static int apc_query_server (char *host, int port,
		struct apc_detail_s *apcups_detail)
{
	int     n;
	char    recvline[1024];
	char   *tokptr;
	char   *toksaveptr;
	char   *key;
	double  value;

	static complain_t compl;

#if APCMAIN
# define PRINT_VALUE(name, val) printf("  Found property: name = %s; value = %f;\n", name, val)
#else
# define PRINT_VALUE(name, val) /**/
#endif

	if (global_sockfd < 0)
	{
		if ((global_sockfd = net_open (host, NULL, port)) < 0)
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

	if (net_send (&global_sockfd, "status", 6) < 0)
	{
		ERROR ("apcups plugin: Writing to the socket failed.");
		return (-1);
	}

	while ((n = net_recv (&global_sockfd, recvline, sizeof (recvline) - 1)) > 0)
	{
		assert (n < sizeof (recvline));
		recvline[n] = '\0';
#if APCMAIN
		printf ("net_recv = `%s';\n", recvline);
#endif /* if APCMAIN */

		toksaveptr = NULL;
		tokptr = strtok_r (recvline, " :\t", &toksaveptr);
		while (tokptr != NULL)
		{
			key = tokptr;
			if ((tokptr = strtok_r (NULL, " :\t", &toksaveptr)) == NULL)
				continue;
			value = atof (tokptr);

			PRINT_VALUE (key, value);

			if (strcmp ("LINEV", key) == 0)
				apcups_detail->linev = value;
			else if (strcmp ("BATTV", key) == 0) 
				apcups_detail->battv = value;
			else if (strcmp ("ITEMP", key) == 0)
				apcups_detail->itemp = value;
			else if (strcmp ("LOADPCT", key) == 0)
				apcups_detail->loadpct = value;
			else if (strcmp ("BCHARGE", key) == 0)
				apcups_detail->bcharge = value;
			else if (strcmp ("OUTPUTV", key) == 0)
				apcups_detail->outputv = value;
			else if (strcmp ("LINEFREQ", key) == 0)
				apcups_detail->linefreq = value;
			else if (strcmp ("TIMELEFT", key) == 0)
				apcups_detail->timeleft = value;

			tokptr = strtok_r (NULL, ":", &toksaveptr);
		} /* while (tokptr != NULL) */
	}
	
	if (n < 0)
	{
		WARNING ("apcups plugin: Error reading from socket");
		return (-1);
	}

	return (0);
}