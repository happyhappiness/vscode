
	get_host_and_port(&host, &port);
	if (!*port)
		port = "<none>";

	memset(&hints, 0, sizeof(hints));
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	if (flags & CONNECT_VERBOSE)
		fprintf(stderr, "Looking up %s ... ", host);

