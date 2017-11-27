static int riemann_connect(struct riemann_host *host) /* {{{ */
{
	int			 e;
	struct addrinfo		*ai, *res, hints;
	char const		*node;
	char const		*service;

	if (host->flags & F_CONNECT)
		return 0;

	memset(&hints, 0, sizeof(hints));
	memset(&service, 0, sizeof(service));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = host->use_tcp ? SOCK_STREAM : SOCK_DGRAM;
#ifdef AI_ADDRCONFIG
	hints.ai_flags |= AI_ADDRCONFIG;
#endif

	node = (host->node != NULL) ? host->node : RIEMANN_HOST;
	service = (host->service != NULL) ? host->service : RIEMANN_PORT;

	if ((e = getaddrinfo(node, service, &hints, &res)) != 0) {
		ERROR ("write_riemann plugin: Unable to resolve host \"%s\": %s",
			node, gai_strerror(e));
		return -1;
	}

	host->s = -1;
	for (ai = res; ai != NULL; ai = ai->ai_next) {
		if ((host->s = socket(ai->ai_family,
				      ai->ai_socktype,
				      ai->ai_protocol)) == -1) {
			continue;
		}

		if (connect(host->s, ai->ai_addr, ai->ai_addrlen) != 0) {
			close(host->s);
			host->s = -1;
			continue;
		}

		host->flags |= F_CONNECT;
		DEBUG("write_riemann plugin: got a successful connection for: %s:%s",
				node, service);
		break;
	}

	freeaddrinfo(res);

	if (host->s < 0) {
		WARNING("write_riemann plugin: Unable to connect to Riemann at %s:%s",
				node, service);
		return -1;
	}
	return 0;
}