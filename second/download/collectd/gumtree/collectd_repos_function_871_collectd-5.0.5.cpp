static int mbmon_query_daemon (char *buffer, int buffer_size)
{
	int fd;
	ssize_t status;
	int buffer_fill;

	const char *host;
	const char *port;

	struct addrinfo  ai_hints;
	struct addrinfo *ai_list, *ai_ptr;
	int              ai_return;

	memset (&ai_hints, '\0', sizeof (ai_hints));
	ai_hints.ai_flags    = 0;
#ifdef AI_ADDRCONFIG
	ai_hints.ai_flags   |= AI_ADDRCONFIG;
#endif
	ai_hints.ai_family   = PF_UNSPEC;
	ai_hints.ai_socktype = SOCK_STREAM;
	ai_hints.ai_protocol = IPPROTO_TCP;

	host = mbmon_host;
	if (host == NULL)
		host = MBMON_DEF_HOST;

	port = mbmon_port;
	if (port == NULL)
		port = MBMON_DEF_PORT;

	if ((ai_return = getaddrinfo (host, port, &ai_hints, &ai_list)) != 0)
	{
		char errbuf[1024];
		ERROR ("mbmon: getaddrinfo (%s, %s): %s",
				host, port,
				(ai_return == EAI_SYSTEM)
				? sstrerror (errno, errbuf, sizeof (errbuf))
				: gai_strerror (ai_return));
		return (-1);
	}

	fd = -1;
	for (ai_ptr = ai_list; ai_ptr != NULL; ai_ptr = ai_ptr->ai_next)
	{
		/* create our socket descriptor */
		if ((fd = socket (ai_ptr->ai_family, ai_ptr->ai_socktype, ai_ptr->ai_protocol)) < 0)
		{
			char errbuf[1024];
			ERROR ("mbmon: socket: %s",
					sstrerror (errno, errbuf,
						sizeof (errbuf)));
			continue;
		}

		/* connect to the mbmon daemon */
		if (connect (fd, (struct sockaddr *) ai_ptr->ai_addr, ai_ptr->ai_addrlen))
		{
			char errbuf[1024];
			INFO ("mbmon: connect (%s, %s): %s", host, port,
					sstrerror (errno, errbuf,
						sizeof (errbuf)));
			close (fd);
			fd = -1;
			continue;
		}

		/* A socket could be opened and connecting succeeded. We're
		 * done. */
		break;
	}

	freeaddrinfo (ai_list);

	if (fd < 0)
	{
		ERROR ("mbmon: Could not connect to daemon.");
		return (-1);
	}

	/* receive data from the mbmon daemon */
	memset (buffer, '\0', buffer_size);

	buffer_fill = 0;
	while ((status = read (fd, buffer + buffer_fill, buffer_size - buffer_fill)) != 0)
	{
		if (status == -1)
		{
			char errbuf[1024];

			if ((errno == EAGAIN) || (errno == EINTR))
				continue;

			ERROR ("mbmon: Error reading from socket: %s",
					sstrerror (errno, errbuf,
						sizeof (errbuf)));
			close (fd);
			return (-1);
		}
		buffer_fill += status;

		if (buffer_fill >= buffer_size)
			break;
	}

	if (buffer_fill >= buffer_size)
	{
		buffer[buffer_size - 1] = '\0';
		WARNING ("mbmon: Message from mbmon has been truncated.");
	}
	else if (buffer_fill == 0)
	{
		WARNING ("mbmon: Peer has unexpectedly shut down the socket. "
				"Buffer: `%s'", buffer);
		close (fd);
		return (-1);
	}

	close (fd);
	return (0);
}