int try_bind_local(int s, int ai_family, int ai_socktype,
		   const char *bind_addr)
{
	int error;
	struct addrinfo bhints, *bres_all, *r;

	memset(&bhints, 0, sizeof bhints);
	bhints.ai_family = ai_family;
	bhints.ai_socktype = ai_socktype;
	bhints.ai_flags = AI_PASSIVE;
	if ((error = getaddrinfo(bind_addr, NULL, &bhints, &bres_all))) {
		rprintf(FERROR, RSYNC_NAME ": getaddrinfo %s: %s\n",
			bind_addr, gai_strerror(error));
		return -1;
	}

	for (r = bres_all; r; r = r->ai_next) {
		if (bind(s, r->ai_addr, r->ai_addrlen) == -1)
			continue;
		freeaddrinfo(bres_all);
		return s;
	}

	/* no error message; there might be some problem that allows
	 * creation of the socket but not binding, perhaps if the
	 * machine has no ipv6 address of this name. */
	freeaddrinfo(bres_all);
	return -1;
}