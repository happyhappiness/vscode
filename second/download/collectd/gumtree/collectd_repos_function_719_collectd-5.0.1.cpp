static int memcached_query_daemon (char *buffer, int buffer_size) /* {{{ */
{
	int fd;
	ssize_t status;
	int buffer_fill;
	int i = 0;

	if (memcached_socket != NULL) {
		struct sockaddr_un serv_addr;

		memset (&serv_addr, 0, sizeof (serv_addr));
		serv_addr.sun_family = AF_UNIX;
		sstrncpy (serv_addr.sun_path, memcached_socket,
				sizeof (serv_addr.sun_path));

		/* create our socket descriptor */
		fd = socket (AF_UNIX, SOCK_STREAM, 0);
		if (fd < 0) {
			char errbuf[1024];
			ERROR ("memcached: unix socket: %s", sstrerror (errno, errbuf,
						sizeof (errbuf)));
			return -1;
		}

		/* connect to the memcached daemon */
		status = (ssize_t) connect (fd, (struct sockaddr *) &serv_addr,
				sizeof (serv_addr));
		if (status != 0) {
			shutdown (fd, SHUT_RDWR);
			close (fd);
			fd = -1;
		}
	}
	else { /* if (memcached_socket == NULL) */
		const char *host;
		const char *port;

		struct addrinfo  ai_hints;
		struct addrinfo *ai_list, *ai_ptr;
		int              ai_return = 0;

		memset (&ai_hints, '\0', sizeof (ai_hints));
		ai_hints.ai_flags    = 0;
#ifdef AI_ADDRCONFIG
		/*	ai_hints.ai_flags   |= AI_ADDRCONFIG; */
#endif
		ai_hints.ai_family   = AF_INET;
		ai_hints.ai_socktype = SOCK_STREAM;
		ai_hints.ai_protocol = 0;

		host = memcached_host;
		if (host == NULL) {
			host = MEMCACHED_DEF_HOST;
		}

		port = memcached_port;
		if (strlen (port) == 0) {
			port = MEMCACHED_DEF_PORT;
		}

		if ((ai_return = getaddrinfo (host, port, &ai_hints, &ai_list)) != 0) {
			char errbuf[1024];
			ERROR ("memcached: getaddrinfo (%s, %s): %s",
					host, port,
					(ai_return == EAI_SYSTEM)
					? sstrerror (errno, errbuf, sizeof (errbuf))
					: gai_strerror (ai_return));
			return -1;
		}

		fd = -1;
		for (ai_ptr = ai_list; ai_ptr != NULL; ai_ptr = ai_ptr->ai_next) {
			/* create our socket descriptor */
			fd = socket (ai_ptr->ai_family, ai_ptr->ai_socktype, ai_ptr->ai_protocol);
			if (fd < 0) {
				char errbuf[1024];
				ERROR ("memcached: socket: %s", sstrerror (errno, errbuf, sizeof (errbuf)));
				continue;
			}

			/* connect to the memcached daemon */
			status = (ssize_t) connect (fd, (struct sockaddr *) ai_ptr->ai_addr, ai_ptr->ai_addrlen);
			if (status != 0) {
				shutdown (fd, SHUT_RDWR);
				close (fd);
				fd = -1;
				continue;
			}

			/* A socket could be opened and connecting succeeded. We're
			 * done. */
			break;
		}

		freeaddrinfo (ai_list);
	}

	if (fd < 0) {
		ERROR ("memcached: Could not connect to daemon.");
		return -1;
	}

	if (send(fd, "stats\r\n", sizeof("stats\r\n") - 1, MSG_DONTWAIT) != (sizeof("stats\r\n") - 1)) {
		ERROR ("memcached: Could not send command to the memcached daemon.");
		return -1;
	}

	{
		struct pollfd p;
		int status;

		memset (&p, 0, sizeof (p));
		p.fd = fd;
		p.events = POLLIN | POLLERR | POLLHUP;
		p.revents = 0;

		status = poll (&p, /* nfds = */ 1,
				/* timeout = */ CDTIME_T_TO_MS (interval_g));
		if (status <= 0)
		{
			if (status == 0)
			{
				ERROR ("memcached: poll(2) timed out after %.3f seconds.",
						CDTIME_T_TO_DOUBLE (interval_g));
			}
			else
			{
				char errbuf[1024];
				ERROR ("memcached: poll(2) failed: %s",
						sstrerror (errno, errbuf, sizeof (errbuf)));
			}
			shutdown (fd, SHUT_RDWR);
			close (fd);
			return (-1);
		}
	}

	/* receive data from the memcached daemon */
	memset (buffer, '\0', buffer_size);

	buffer_fill = 0;
	while ((status = recv (fd, buffer + buffer_fill, buffer_size - buffer_fill, MSG_DONTWAIT)) != 0) {
		if (i > MEMCACHED_RETRY_COUNT) {
			ERROR("recv() timed out");
			break;
		}
		i++;

		if (status == -1) {
			char errbuf[1024];

			if (errno == EAGAIN) {
				continue;
			}

			ERROR ("memcached: Error reading from socket: %s",
					sstrerror (errno, errbuf, sizeof (errbuf)));
			shutdown(fd, SHUT_RDWR);
			close (fd);
			return -1;
		}
		buffer_fill += status;

		if (buffer_fill > 3 && buffer[buffer_fill-5] == 'E' && buffer[buffer_fill-4] == 'N' && buffer[buffer_fill-3] == 'D') {
			/* we got all the data */
			break;
		}
	}

	if (buffer_fill >= buffer_size) {
		buffer[buffer_size - 1] = '\0';
		WARNING ("memcached: Message from memcached has been truncated.");
	} else if (buffer_fill == 0) {
		WARNING ("memcached: Peer has unexpectedly shut down the socket. "
				"Buffer: `%s'", buffer);
		shutdown(fd, SHUT_RDWR);
		close(fd);
		return -1;
	}

	shutdown(fd, SHUT_RDWR);
	close(fd);
	return 0;
}