	int     n;
	char    recvline[1024];
	char   *tokptr;
	char   *toksaveptr;
	char   *key;
	double  value;
	_Bool retry = 1;
	int status;

#if APCMAIN
# define PRINT_VALUE(name, val) printf("  Found property: name = %s; value = %f;\n", name, val)
#else
# define PRINT_VALUE(name, val) /**/
#endif

	while (retry)
	{
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


		status = net_send (&global_sockfd, "status", strlen ("status"));
		if (status != 0)
		{
			/* net_send is closing the socket on error. */
			assert (global_sockfd < 0);
			if (retry)
			{
				retry = 0;
				count_retries++;
				continue;
			}

			ERROR ("apcups plugin: Writing to the socket failed.");
			return (-1);
		}

		break;
	} /* while (retry) */

        /* When collectd's collection interval is larger than apcupsd's
         * timeout, we would have to retry / re-connect each iteration. Try to
         * detect this situation and shut down the socket gracefully in that
         * case. Otherwise, keep the socket open to avoid overhead. */
	count_iterations++;
	if ((count_iterations == 10) && (count_retries > 2))
	{
		NOTICE ("apcups plugin: There have been %i retries in the "
				"first %i iterations. Will close the socket "
				"in future iterations.",
				count_retries, count_iterations);
		close_socket = 1;
	}

	while ((n = net_recv (&global_sockfd, recvline, sizeof (recvline) - 1)) > 0)
	{
		assert ((unsigned int)n < sizeof (recvline));
		recvline[n] = '\0';
