int open_socket_out(char *host, int port, const char *bind_address,
		    int af_hint)
{
	int type = SOCK_STREAM;
	int error;
	int s;
	struct addrinfo hints, *res0, *res;
	char portbuf[10];
	char *h;
	int proxied = 0;
	char buffer[1024];
	char *cp;

	/* if we have a RSYNC_PROXY env variable then redirect our
	 * connetcion via a web proxy at the given address. The format
	 * is hostname:port */
	h = getenv("RSYNC_PROXY");
	proxied = (h != NULL) && (*h != '\0');

	if (proxied) {
		strlcpy(buffer, h, sizeof(buffer));
		cp = strchr(buffer, ':');
		if (cp == NULL) {
			rprintf(FERROR,
				"invalid proxy specification: should be HOST:PORT\n");
			return -1;
		}
		*cp++ = '\0';
		strcpy(portbuf, cp);
		h = buffer;
		if (verbose >= 2) {
			rprintf(FINFO, "connection via http proxy %s port %s\n",
				h, portbuf);
		}
	} else {
		snprintf(portbuf, sizeof(portbuf), "%d", port);
		h = host;
	}

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = af_hint;
	hints.ai_socktype = type;
	error = getaddrinfo(h, portbuf, &hints, &res0);
	if (error) {
		rprintf(FERROR, RSYNC_NAME ": getaddrinfo: %s %s: %s\n",
			h, portbuf, gai_strerror(error));
		return -1;
	}

	s = -1;
	/* Try to connect to all addresses for this machine until we get
	 * through.  It might e.g. be multi-homed, or have both IPv4 and IPv6
	 * addresses.  We need to create a socket for each record, since the
	 * address record tells us what protocol to use to try to connect. */
	for (res = res0; res; res = res->ai_next) {
		s = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
		if (s < 0)
			continue;

		if (bind_address)
			if (try_bind_local(s, res->ai_family, type,
					   bind_address) == -1) {
				close(s);
				s = -1;
				continue;
			}

		if (connect(s, res->ai_addr, res->ai_addrlen) < 0) {
			close(s);
			s = -1;
			continue;
		}
		if (proxied &&
		    establish_proxy_connection(s, host, port) != 0) {
			close(s);
			s = -1;
			continue;
		} else
			break;
	}
	freeaddrinfo(res0);
	if (s < 0) {
		rprintf(FERROR, RSYNC_NAME ": failed to connect to %s: %s\n",
			h, strerror(errno));
		return -1;
	}
	return s;
}