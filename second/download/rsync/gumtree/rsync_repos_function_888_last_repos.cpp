static int getaddr_info_single_addr(const char *service,
				uint32 addr,
				const struct addrinfo *hints,
				struct addrinfo **res)
{

	struct addrinfo *ai = NULL;
	struct in_addr ip;
	unsigned short port = 0;

	if (service) {
		port = (unsigned short)atoi(service);
	}
	ip.s_addr = htonl(addr);

	ai = alloc_entry(hints, ip, port);
	if (!ai) {
		return EAI_MEMORY;
	}

	/* If we're asked for the canonical name,
	 * make sure it returns correctly. */
	if (!(hints->ai_flags & AI_NUMERICSERV) &&
			hints->ai_flags & AI_CANONNAME) {
		int err;
		if (addr == INADDR_LOOPBACK || addr == INADDR_ANY) {
			ai->ai_canonname = get_my_canon_name(&err);
		} else {
			ai->ai_canonname =
			get_canon_name_from_addr(ip,&err);
		}
		if (ai->ai_canonname == NULL) {
			freeaddrinfo(ai);
			return err;
		}
	}

	*res = ai;
	return 0;
}