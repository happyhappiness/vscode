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

	/* We don't support those. */
	if ((node && !(flags & NI_NUMERICHOST))
		|| (service && !(flags & NI_NUMERICSERV)))
		return EAI_FAIL;

	if (node) {
		return gethostnameinfo(sa, node, nodelen, flags);
	}

	if (service) {
		return getservicenameinfo(sa, service, servicelen, flags);
	}
	return 0;
}