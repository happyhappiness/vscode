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
