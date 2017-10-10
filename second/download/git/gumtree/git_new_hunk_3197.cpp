
	get_host_and_port(&host, &port);
	if (!*port)
		port = "<none>";

	memset(&hints, 0, sizeof(hints));
	if (flags & CONNECT_IPV4)
		hints.ai_family = AF_INET;
	else if (flags & CONNECT_IPV6)
		hints.ai_family = AF_INET6;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	if (flags & CONNECT_VERBOSE)
		fprintf(stderr, "Looking up %s ... ", host);

