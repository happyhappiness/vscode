static int sensu_connect(struct sensu_host *host) /* {{{ */
{
	int			 e;
	char const		*node;
	char const		*service;

	// Resolve the target if we haven't done already
	if (!(host->flags & F_READY)) {
		memset(&service, 0, sizeof(service));
		host->res = NULL;

		node = (host->node != NULL) ? host->node : SENSU_HOST;
		service = (host->service != NULL) ? host->service : SENSU_PORT;

		struct addrinfo ai_hints = {
			.ai_family = AF_INET,
			.ai_flags = AI_ADDRCONFIG,
			.ai_socktype = SOCK_STREAM
		};

		if ((e = getaddrinfo(node, service, &ai_hints, &(host->res))) != 0) {
			ERROR("write_sensu plugin: Unable to resolve host \"%s\": %s",
					node, gai_strerror(e));
			return -1;
		}
		DEBUG("write_sensu plugin: successfully resolved host/port: %s/%s",
				node, service);
		host->flags |= F_READY;
	}

	struct linger so_linger;
	host->s = -1;
	for (struct addrinfo *ai = host->res; ai != NULL; ai = ai->ai_next) {
		// create the socket
		if ((host->s = socket(ai->ai_family,
				      ai->ai_socktype,
				      ai->ai_protocol)) == -1) {
			continue;
		}

		// Set very low close() lingering
		so_linger.l_onoff = 1;
		so_linger.l_linger = 3;
		if (setsockopt(host->s, SOL_SOCKET, SO_LINGER, &so_linger, sizeof so_linger) != 0)
			WARNING("write_sensu plugin: failed to set socket close() lingering");

		set_sock_opts(host->s);

		// connect the socket
		if (connect(host->s, ai->ai_addr, ai->ai_addrlen) != 0) {
			close(host->s);
			host->s = -1;
			continue;
		}
		DEBUG("write_sensu plugin: connected");
		break;
	}

	if (host->s < 0) {
		WARNING("write_sensu plugin: Unable to connect to sensu client");
		return -1;
	}
	return 0;
}