static int *open_socket_in(int type, int port, const char *bind_address,
			   int af_hint)
{
	int one=1;
	int s, *sp, *socks, maxs;
	struct addrinfo hints, *all_ai, *resp;
	char portbuf[10];
	int error;

	memset(&hints, 0, sizeof hints);
	hints.ai_family = af_hint;
	hints.ai_socktype = type;
	hints.ai_flags = AI_PASSIVE;
	snprintf(portbuf, sizeof portbuf, "%d", port);
	error = getaddrinfo(bind_address, portbuf, &hints, &all_ai);
	if (error) {
		rprintf(FERROR, RSYNC_NAME ": getaddrinfo: bind address %s: %s\n",
			bind_address, gai_strerror(error));
		return NULL;
	}

	/* Count max number of sockets we might open. */
	for (maxs = 0, resp = all_ai; resp; resp = resp->ai_next, maxs++) {}
	socks = new_array(int, maxs + 1);
	if (!socks) {
		rprintf(FERROR,
			RSYNC_NAME "couldn't allocate memory for sockets");
		return NULL;
	}

	/* We may not be able to create the socket, if for example the
	 * machine knows about IPv6 in the C library, but not in the
	 * kernel. */
	sp = socks + 1; /* Leave room for count at start of array. */
	for (resp = all_ai; resp; resp = resp->ai_next) {
		s = socket(resp->ai_family, resp->ai_socktype,
			   resp->ai_protocol);

		if (s == -1) {
			/* See if there's another address that will work... */
			continue;
		}

		setsockopt(s, SOL_SOCKET, SO_REUSEADDR,
			   (char *)&one, sizeof one);

#ifdef IPV6_V6ONLY
		if (resp->ai_family == AF_INET6) {
			setsockopt(s, IPPROTO_IPV6, IPV6_V6ONLY,
				   (char *)&one, sizeof one);
		}
#endif

		/* Now we've got a socket - we need to bind it. */
		if (bind(s, resp->ai_addr, resp->ai_addrlen) < 0) {
			/* Nope, try another */
			close(s);
			continue;
		}

		*sp++ = s;
	}
	*socks = sp - socks - 1;   /* Save count. */

	if (all_ai)
		freeaddrinfo(all_ai);

	if (*socks == 0) {
		rprintf(FERROR,
			RSYNC_NAME ": open inbound socket on port %d failed: "
			"%s\n", port, strerror(errno));
		free(socks);
		return NULL;
	}
	return socks;
}