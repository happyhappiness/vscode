int getnameinfo(const struct sockaddr *sa, socklen_t salen,
			char *node, size_t nodelen,
			char *service, size_t servicelen, int flags)
{

	/* Invalid arguments. */
	if (sa == NULL || (node == NULL && service == NULL)) {
		return EAI_FAIL;
	}

	if (sa->sa_family != AF_INET) {
		return EAI_FAIL;
	}

	if (salen < (socklen_t)sizeof (struct sockaddr_in)) {
		return EAI_FAIL;
	}

	if (node) {
		int ret = gethostnameinfo(sa, node, nodelen, flags);
		if (ret)
			return ret;
	}

	if (service) {
		return getservicenameinfo(sa, service, servicelen, flags);
	}
	return 0;
}