static int net_open (char *host, char *service, int port)
{
	int              sd;
	int              status;
	char             port_str[8];
	struct addrinfo  ai_hints;
	struct addrinfo *ai_return;
	struct addrinfo *ai_list;

	assert ((port > 0x00000000) && (port <= 0x0000FFFF));

	/* Convert the port to a string */
	snprintf (port_str, 8, "%i", port);
	port_str[7] = '\0';

	/* Resolve name */
	memset ((void *) &ai_hints, '\0', sizeof (ai_hints));
	ai_hints.ai_family   = AF_INET; /* XXX: Change this to `AF_UNSPEC' if apcupsd can handle IPv6 */
	ai_hints.ai_socktype = SOCK_STREAM;

	status = getaddrinfo (host, port_str, &ai_hints, &ai_return);
	if (status != 0)
	{
		char errbuf[1024];
		INFO ("getaddrinfo failed: %s",
				(status == EAI_SYSTEM)
				? sstrerror (errno, errbuf, sizeof (errbuf))
				: gai_strerror (status));
		return (-1);
	}

	/* Create socket */
	sd = -1;
	for (ai_list = ai_return; ai_list != NULL; ai_list = ai_list->ai_next)
	{
		sd = socket (ai_list->ai_family, ai_list->ai_socktype, ai_list->ai_protocol);
		if (sd >= 0)
			break;
	}
	/* `ai_list' still holds the current description of the socket.. */

	if (sd < 0)
	{
		DEBUG ("Unable to open a socket");
		freeaddrinfo (ai_return);
		return (-1);
	}

	status = connect (sd, ai_list->ai_addr, ai_list->ai_addrlen);

	freeaddrinfo (ai_return);

	if (status != 0) /* `connect(2)' failed */
	{
		char errbuf[1024];
		INFO ("connect failed: %s",
				sstrerror (errno, errbuf, sizeof (errbuf)));
		close (sd);
		return (-1);
	}

	DEBUG ("Done opening a socket %i", sd);

	return (sd);
}