char *client_name(int fd)
{
	static char name_buf[100];
	static char port_buf[100];
	static int initialised;
	struct sockaddr_storage ss;
	socklen_t ss_len;

	if (initialised)
		return name_buf;

	strlcpy(name_buf, default_name, sizeof name_buf);
	initialised = 1;

	memset(&ss, 0, sizeof ss);

	if (am_server) {	/* daemon over --rsh mode */
		char *addr = client_addr(fd);
		struct addrinfo hint, *answer;
		int err;

		if (strcmp(addr, "0.0.0.0") == 0)
			return name_buf;

		memset(&hint, 0, sizeof hint);

#ifdef AI_NUMERICHOST
		hint.ai_flags = AI_NUMERICHOST;
#endif
		hint.ai_socktype = SOCK_STREAM;

		if ((err = getaddrinfo(addr, NULL, &hint, &answer)) != 0) {
			rprintf(FLOG, "malformed address %s: %s\n",
			        addr, gai_strerror(err));
			return name_buf;
		}

		switch (answer->ai_family) {
		case AF_INET:
			ss_len = sizeof (struct sockaddr_in);
			memcpy(&ss, answer->ai_addr, ss_len);
			break;
#ifdef INET6
		case AF_INET6:
			ss_len = sizeof (struct sockaddr_in6);
			memcpy(&ss, answer->ai_addr, ss_len);
			break;
#endif
		default:
			exit_cleanup(RERR_SOCKETIO);
		}
		freeaddrinfo(answer);
	} else {
		ss_len = sizeof ss;
		client_sockaddr(fd, &ss, &ss_len);
	}

	if (lookup_name(fd, &ss, ss_len, name_buf, sizeof name_buf,
			port_buf, sizeof port_buf) == 0)
		check_name(fd, &ss, name_buf, sizeof name_buf);

	return name_buf;
}