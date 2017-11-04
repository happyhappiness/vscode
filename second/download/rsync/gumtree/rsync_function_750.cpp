static int *open_socket_in(int type, int port, const char *bind_addr,
			   int af_hint)
{
	int one = 1;
	int s, *socks, maxs, i, ecnt;
	struct addrinfo hints, *all_ai, *resp;
	char portbuf[10], **errmsgs;
	int error;

	memset(&hints, 0, sizeof hints);
	hints.ai_family = af_hint;
	hints.ai_socktype = type;
	hints.ai_flags = AI_PASSIVE;
	snprintf(portbuf, sizeof portbuf, "%d", port);
	error = getaddrinfo(bind_addr, portbuf, &hints, &all_ai);
	if (error) {
		rprintf(FERROR, RSYNC_NAME ": getaddrinfo: bind address %s: %s\n",
			bind_addr, gai_strerror(error));
		return NULL;
	}

	/* Count max number of sockets we might open. */
	for (maxs = 0, resp = all_ai; resp; resp = resp->ai_next, maxs++) {}

	socks = new_array(int, maxs + 1);
	errmsgs = new_array(char *, maxs);
	if (!socks || !errmsgs)
		out_of_memory("open_socket_in");

	/* We may not be able to create the socket, if for example the
	 * machine knows about IPv6 in the C library, but not in the
	 * kernel. */
	for (resp = all_ai, i = ecnt = 0; resp; resp = resp->ai_next) {
		s = socket(resp->ai_family, resp->ai_socktype,
			   resp->ai_protocol);

		if (s == -1) {
			int r = asprintf(&errmsgs[ecnt++],
				"socket(%d,%d,%d) failed: %s\n",
				(int)resp->ai_family, (int)resp->ai_socktype,
				(int)resp->ai_protocol, strerror(errno));
			if (r < 0)
				out_of_memory("open_socket_in");
			/* See if there's another address that will work... */
			continue;
		}

		setsockopt(s, SOL_SOCKET, SO_REUSEADDR,
			   (char *)&one, sizeof one);

#ifdef IPV6_V6ONLY
		if (resp->ai_family == AF_INET6) {
			if (setsockopt(s, IPPROTO_IPV6, IPV6_V6ONLY,
				       (char *)&one, sizeof one) < 0
			    && default_af_hint != AF_INET6) {
				close(s);
				continue;
			}
		}
#endif

		/* Now we've got a socket - we need to bind it. */
		if (bind(s, resp->ai_addr, resp->ai_addrlen) < 0) {
			/* Nope, try another */
			int r = asprintf(&errmsgs[ecnt++],
				"bind() failed: %s (address-family %d)\n",
				strerror(errno), (int)resp->ai_family);
			if (r < 0)
				out_of_memory("open_socket_in");
			close(s);
			continue;
		}

		socks[i++] = s;
	}
	socks[i] = -1;

	if (all_ai)
		freeaddrinfo(all_ai);

	/* Only output the socket()/bind() messages if we were totally
	 * unsuccessful, or if the daemon is being run with -vv. */
	for (s = 0; s < ecnt; s++) {
		if (!i || verbose > 1)
			rwrite(FLOG, errmsgs[s], strlen(errmsgs[s]));
		free(errmsgs[s]);
	}
	free(errmsgs);

	if (!i) {
		rprintf(FERROR,
			"unable to bind any inbound sockets on port %d\n",
			port);
		free(socks);
		return NULL;
	}
	return socks;
}