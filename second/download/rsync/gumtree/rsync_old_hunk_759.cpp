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
