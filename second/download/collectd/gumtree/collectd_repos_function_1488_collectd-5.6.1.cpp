static int hddtemp_query_daemon (char *buffer, int buffer_size)
{
	int fd;
	ssize_t status;
	int buffer_fill;

	const char *host;
	const char *port;

	struct addrinfo *ai_list;
	int              ai_return;

	host = hddtemp_host;
	if (host == NULL)
		host = HDDTEMP_DEF_HOST;

	port = hddtemp_port;
	if (strlen (port) == 0)
		port = HDDTEMP_DEF_PORT;

	struct addrinfo ai_hints = {
		.ai_flags = AI_ADDRCONFIG,
		.ai_family = AF_UNSPEC,
		.ai_protocol = IPPROTO_TCP,
		.ai_socktype = SOCK_STREAM
	};

	if ((ai_return = getaddrinfo (host, port, &ai_hints, &ai_list)) != 0)
	{
		char errbuf[1024];
		ERROR ("hddtemp plugin: getaddrinfo (%s, %s): %s",
				host, port,
				(ai_return == EAI_SYSTEM)
				? sstrerror (errno, errbuf, sizeof (errbuf))
				: gai_strerror (ai_return));
		return (-1);
	}

	fd = -1;
	for (struct addrinfo *ai_ptr = ai_list; ai_ptr != NULL; ai_ptr = ai_ptr->ai_next)
	{
		/* create our socket descriptor */
		fd = socket (ai_ptr->ai_family, ai_ptr->ai_socktype,
				ai_ptr->ai_protocol);
		if (fd < 0)
		{
			char errbuf[1024];
			ERROR ("hddtemp plugin: socket: %s",
					sstrerror (errno, errbuf, sizeof (errbuf)));
			continue;
		}

		/* connect to the hddtemp daemon */
		if (connect (fd, (struct sockaddr *) ai_ptr->ai_addr,
					ai_ptr->ai_addrlen))
		{
			char errbuf[1024];
			INFO ("hddtemp plugin: connect (%s, %s) failed: %s",
					host, port,
					sstrerror (errno, errbuf, sizeof (errbuf)));
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
		ERROR ("hddtemp plugin: Could not connect to daemon.");
		return (-1);
	}

	/* receive data from the hddtemp daemon */
	memset (buffer, '\0', buffer_size);

	buffer_fill = 0;
	while ((status = read (fd, buffer + buffer_fill, buffer_size - buffer_fill)) != 0)
	{
		if (status == -1)
		{
			char errbuf[1024];

			if ((errno == EAGAIN) || (errno == EINTR))
				continue;

			ERROR ("hddtemp plugin: Error reading from socket: %s",
					sstrerror (errno, errbuf, sizeof (errbuf)));
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
		WARNING ("hddtemp plugin: Message from hddtemp has been "
				"truncated.");
	}
	else if (buffer_fill == 0)
	{
		WARNING ("hddtemp plugin: Peer has unexpectedly shut down "
				"the socket. Buffer: `%s'", buffer);
		close (fd);
		return (-1);
	}

	close (fd);
	return (0);
}