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
#if APCMAIN
		printf ("net_recv = `%s';\n", recvline);
#endif /* if APCMAIN */

		toksaveptr = NULL;
		tokptr = strtok_r (recvline, " :\t", &toksaveptr);
		while (tokptr != NULL)
		{
			char *key = tokptr;
			if ((tokptr = strtok_r (NULL, " :\t", &toksaveptr)) == NULL)
				continue;

			gauge_t value;
			if (strtogauge (tokptr, &value) != 0)
				continue;

			PRINT_VALUE (key, value);

			if (strcmp ("LINEV", key) == 0)
				apcups_detail->linev = value;
			else if (strcmp ("BATTV", key) == 0)
