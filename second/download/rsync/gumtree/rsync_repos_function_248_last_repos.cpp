int open_socket_out(char *host, int port, const char *bind_addr,
		    int af_hint)
{
	int type = SOCK_STREAM;
	int error, s, j, addr_cnt, *errnos;
	struct addrinfo hints, *res0, *res;
	char portbuf[10];
	char *h, *cp;
	int proxied = 0;
	char buffer[1024];
	char *proxy_user = NULL, *proxy_pass = NULL;

	/* if we have a RSYNC_PROXY env variable then redirect our
	 * connetcion via a web proxy at the given address. */
	h = getenv("RSYNC_PROXY");
	proxied = h != NULL && *h != '\0';

	if (proxied) {
		strlcpy(buffer, h, sizeof buffer);

		/* Is the USER:PASS@ prefix present? */
		if ((cp = strrchr(buffer, '@')) != NULL) {
			*cp++ = '\0';
			/* The remainder is the HOST:PORT part. */
			h = cp;

			if ((cp = strchr(buffer, ':')) == NULL) {
				rprintf(FERROR,
					"invalid proxy specification: should be USER:PASS@HOST:PORT\n");
				return -1;
			}
			*cp++ = '\0';

			proxy_user = buffer;
			proxy_pass = cp;
		} else {
			/* The whole buffer is the HOST:PORT part. */
			h = buffer;
		}

		if ((cp = strchr(h, ':')) == NULL) {
			rprintf(FERROR,
				"invalid proxy specification: should be HOST:PORT\n");
			return -1;
		}
		*cp++ = '\0';
		strlcpy(portbuf, cp, sizeof portbuf);
		if (DEBUG_GTE(CONNECT, 1)) {
			rprintf(FINFO, "connection via http proxy %s port %s\n",
				h, portbuf);
		}
	} else {
		snprintf(portbuf, sizeof portbuf, "%d", port);
		h = host;
	}

	memset(&hints, 0, sizeof hints);
	hints.ai_family = af_hint;
	hints.ai_socktype = type;
	error = getaddrinfo(h, portbuf, &hints, &res0);
	if (error) {
		rprintf(FERROR, RSYNC_NAME ": getaddrinfo: %s %s: %s\n",
			h, portbuf, gai_strerror(error));
		return -1;
	}

	for (res = res0, addr_cnt = 0; res; res = res->ai_next, addr_cnt++) {}
	errnos = new_array0(int, addr_cnt);
	if (!errnos)
		out_of_memory("open_socket_out");

	s = -1;
	/* Try to connect to all addresses for this machine until we get
	 * through.  It might e.g. be multi-homed, or have both IPv4 and IPv6
	 * addresses.  We need to create a socket for each record, since the
	 * address record tells us what protocol to use to try to connect. */
	for (res = res0, j = 0; res; res = res->ai_next, j++) {
		s = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
		if (s < 0)
			continue;

		if (bind_addr
		 && try_bind_local(s, res->ai_family, type,
				   bind_addr) == -1) {
			close(s);
			s = -1;
			continue;
		}
		if (connect_timeout > 0) {
			SIGACTION(SIGALRM, contimeout_handler);
			alarm(connect_timeout);
		}

		set_socket_options(s, sockopts);
		while (connect(s, res->ai_addr, res->ai_addrlen) < 0) {
			if (connect_timeout < 0)
				exit_cleanup(RERR_CONTIMEOUT);
			if (errno == EINTR)
				continue;
			close(s);
			s = -1;
			break;
		}

		if (connect_timeout > 0)
			alarm(0);

		if (s < 0) {
			errnos[j] = errno;
			continue;
		}

		if (proxied
		 && establish_proxy_connection(s, host, port,
					       proxy_user, proxy_pass) != 0) {
			close(s);
			s = -1;
			continue;
		}
		if (DEBUG_GTE(CONNECT, 2)) {
			char buf[2048];
			if ((error = getnameinfo(res->ai_addr, res->ai_addrlen, buf, sizeof buf, NULL, 0, NI_NUMERICHOST)) != 0)
				snprintf(buf, sizeof buf, "*getnameinfo failure: %s*", gai_strerror(error));
			rprintf(FINFO, "Connected to %s (%s)\n", h, buf);
		}
		break;
	}

	if (s < 0 || DEBUG_GTE(CONNECT, 2)) {
		char buf[2048];
		for (res = res0, j = 0; res; res = res->ai_next, j++) {
			if (errnos[j] == 0)
				continue;
			if ((error = getnameinfo(res->ai_addr, res->ai_addrlen, buf, sizeof buf, NULL, 0, NI_NUMERICHOST)) != 0)
				snprintf(buf, sizeof buf, "*getnameinfo failure: %s*", gai_strerror(error));
			rsyserr(FERROR, errnos[j], "failed to connect to %s (%s)", h, buf);
		}
		if (s < 0)
			s = -1;
	}

	freeaddrinfo(res0);
	free(errnos);

	return s;
}