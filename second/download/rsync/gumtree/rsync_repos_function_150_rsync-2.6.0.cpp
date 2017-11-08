static int open_socket_in(int type, int port, const char *bind_address,
			  int af_hint)
{
	int one=1;
	int s;
	struct addrinfo hints, *all_ai, *resp;
	char portbuf[10];
	int error;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = af_hint;
	hints.ai_socktype = type;
	hints.ai_flags = AI_PASSIVE;
	snprintf(portbuf, sizeof(portbuf), "%d", port);
	error = getaddrinfo(bind_address, portbuf, &hints, &all_ai);
	if (error) {
		rprintf(FERROR, RSYNC_NAME ": getaddrinfo: bind address %s: %s\n",
			bind_address, gai_strerror(error));
		return -1;
	}

	/* We may not be able to create the socket, if for example the
	 * machine knows about IPv6 in the C library, but not in the
	 * kernel. */
	for (resp = all_ai; resp; resp = resp->ai_next) {
		s = socket(resp->ai_family, resp->ai_socktype,
			   resp->ai_protocol);

		if (s == -1) 
			/* See if there's another address that will work... */
			continue;
		
		setsockopt(s, SOL_SOCKET, SO_REUSEADDR,
			   (char *)&one, sizeof one);
		
		/* now we've got a socket - we need to bind it */
		if (bind(s, all_ai->ai_addr, all_ai->ai_addrlen) < 0) {
			/* Nope, try another */
			close(s);
			continue;
		}

		freeaddrinfo(all_ai);
		return s;
	}

	rprintf(FERROR, RSYNC_NAME ": open inbound socket on port %d failed: "
		"%s\n",
		port, 
		strerror(errno));

	freeaddrinfo(all_ai);
	return -1; 
}