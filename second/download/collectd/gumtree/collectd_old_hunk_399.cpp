	int     n;
	char    recvline[1024];
	char   *tokptr;
	char   *toksaveptr;
	char   *key;
	double  value;

#if APCMAIN
# define PRINT_VALUE(name, val) printf("  Found property: name = %s; value = %f;\n", name, val)
#else
# define PRINT_VALUE(name, val) /**/
#endif

	if (global_sockfd < 0)
	{
		global_sockfd = net_open (host, port);
		if (global_sockfd < 0)
		{
			ERROR ("apcups plugin: Connecting to the "
					"apcupsd failed.");
			return (-1);
		}
	}

	if (net_send (&global_sockfd, "status", 6) < 0)
	{
		ERROR ("apcups plugin: Writing to the socket failed.");
		return (-1);
	}

	while ((n = net_recv (&global_sockfd, recvline, sizeof (recvline) - 1)) > 0)
	{
		assert ((unsigned int)n < sizeof (recvline));
		recvline[n] = '\0';
