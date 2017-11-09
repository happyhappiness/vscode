static int getaddr_info_name(const char *node,
				const char *service,
				const struct addrinfo *hints,
				struct addrinfo **res)
{
	struct addrinfo *listp = NULL, *prevp = NULL;
	char **pptr = NULL;
	int err;
	struct hostent *hp = NULL;
	unsigned short port = 0;

	if (service) {
		port = (unsigned short)atoi(service);
	}

	hp = gethostbyname(node);
	err = check_hostent_err(hp);
	if (err) {
		return err;
	}

	for(pptr = hp->h_addr_list; *pptr; pptr++) {
		struct in_addr ip = *(struct in_addr *)*pptr;
		struct addrinfo *ai = alloc_entry(hints, ip, port);

		if (!ai) {
			freeaddrinfo(listp);
			return EAI_MEMORY;
		}

		if (!listp) {
			listp = ai;
			prevp = ai;
			ai->ai_canonname = SMB_STRDUP(hp->h_name);
			if (!ai->ai_canonname) {
				freeaddrinfo(listp);
				return EAI_MEMORY;
			}
		} else {
			prevp->ai_next = ai;
			prevp = ai;
		}
	}
	*res = listp;
	return 0;
}