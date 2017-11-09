int getaddrinfo(const char *node,
		const char *service,
		const struct addrinfo * hintp,
		struct addrinfo ** res)
{
	struct addrinfo hints;

	/* Setup the hints struct. */
	if (hintp == NULL) {
		memset(&hints, 0, sizeof(hints));
		hints.ai_family = AF_INET;
		hints.ai_socktype = SOCK_STREAM;
	} else {
		memcpy(&hints, hintp, sizeof(hints));
	}

	if (hints.ai_family != AF_INET && hints.ai_family != AF_UNSPEC) {
		return EAI_FAMILY;
	}

	if (hints.ai_socktype == 0) {
		hints.ai_socktype = SOCK_STREAM;
	}

	if (!node && !service) {
		return EAI_NONAME;
	}

	if (node) {
		if (node[0] == '\0') {
			return getaddr_info_single_addr(service,
					INADDR_ANY,
					&hints,
					res);
		} else if (hints.ai_flags & AI_NUMERICHOST) {
			struct in_addr ip;
			if (inet_pton(AF_INET, node, &ip) <= 0)
				return EAI_FAIL;
			return getaddr_info_single_addr(service,
					ntohl(ip.s_addr),
					&hints,
					res);
		} else {
			return getaddr_info_name(node,
						service,
						&hints,
						res);
		}
	} else if (hints.ai_flags & AI_PASSIVE) {
		return getaddr_info_single_addr(service,
					INADDR_ANY,
					&hints,
					res);
	}
	return getaddr_info_single_addr(service,
					INADDR_LOOPBACK,
					&hints,
					res);
}