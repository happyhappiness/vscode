static int ntpd_connect (void)
{
	char *host;
	char *port;

	struct addrinfo  ai_hints;
	struct addrinfo *ai_list;
	struct addrinfo *ai_ptr;
	int              status;

	if (sock_descr >= 0)
		return (sock_descr);

	DEBUG ("Opening a new socket");

	host = ntpd_host;
	if (host == NULL)
		host = NTPD_DEFAULT_HOST;

	port = ntpd_port;
	if (strlen (port) == 0)
		port = NTPD_DEFAULT_PORT;

	memset (&ai_hints, '\0', sizeof (ai_hints));
	ai_hints.ai_flags    = 0;
#ifdef AI_ADDRCONFIG
	ai_hints.ai_flags   |= AI_ADDRCONFIG;
#endif
	ai_hints.ai_family   = PF_UNSPEC;
	ai_hints.ai_socktype = SOCK_DGRAM;
	ai_hints.ai_protocol = IPPROTO_UDP;

	if ((status = getaddrinfo (host, port, &ai_hints, &ai_list)) != 0)
	{
		char errbuf[1024];
		ERROR ("ntpd plugin: getaddrinfo (%s, %s): %s",
				host, port,
				(status == EAI_SYSTEM)
				? sstrerror (errno, errbuf, sizeof (errbuf))
				: gai_strerror (status));
		return (-1);
	}

	for (ai_ptr = ai_list; ai_ptr != NULL; ai_ptr = ai_ptr->ai_next)
	{
		/* create our socket descriptor */
		if ((sock_descr = socket (ai_ptr->ai_family,
						ai_ptr->ai_socktype,
						ai_ptr->ai_protocol)) < 0)
			continue;

		/* connect to the ntpd */
		if (connect (sock_descr, ai_ptr->ai_addr, ai_ptr->ai_addrlen))
		{
			close (sock_descr);
			sock_descr = -1;
			continue;
		}

		break;
	}

	freeaddrinfo (ai_list);

	if (sock_descr < 0)
	{
		DEBUG ("Unable to connect to server.");
		ERROR ("ntpd plugin: Unable to connect to server.");
	}

	return (sock_descr);
}