static struct addrinfo *alloc_entry(const struct addrinfo *hints,
				struct in_addr ip,
				unsigned short port)
{
	struct sockaddr_in *psin = NULL;
	struct addrinfo *ai = SMB_MALLOC(sizeof(*ai));

	if (!ai) {
		return NULL;
	}
	memset(ai, '\0', sizeof(*ai));

	psin = SMB_MALLOC(sizeof(*psin));
	if (!psin) {
		free(ai);
		return NULL;
	}

	memset(psin, '\0', sizeof(*psin));

	psin->sin_family = AF_INET;
	psin->sin_port = htons(port);
	psin->sin_addr = ip;

	ai->ai_flags = 0;
	ai->ai_family = AF_INET;
	ai->ai_socktype = hints->ai_socktype;
	ai->ai_protocol = hints->ai_protocol;
	ai->ai_addrlen = sizeof(*psin);
	ai->ai_addr = (struct sockaddr *) psin;
	ai->ai_canonname = NULL;
	ai->ai_next = NULL;

	return ai;
}