static int gethostnameinfo(const struct sockaddr *sa,
			char *node,
			size_t nodelen,
			int flags)
{
	int ret = -1;
	char *p = NULL;

	if (!(flags & NI_NUMERICHOST)) {
		struct hostent *hp = gethostbyaddr(
				(void *)&((struct sockaddr_in *)sa)->sin_addr,
				sizeof (struct in_addr),
				sa->sa_family);
		ret = check_hostent_err(hp);
		if (ret == 0) {
			/* Name looked up successfully. */
			ret = snprintf(node, nodelen, "%s", hp->h_name);
			if (ret < 0 || (size_t)ret >= nodelen) {
				return EAI_MEMORY;
			}
			if (flags & NI_NOFQDN) {
				p = strchr(node,'.');
				if (p) {
					*p = '\0';
				}
			}
			return 0;
		}

		if (flags & NI_NAMEREQD) {
			/* If we require a name and didn't get one,
			 * automatically fail. */
			return ret;
		}
		/* Otherwise just fall into the numeric host code... */
	}
	p = inet_ntoa(((struct sockaddr_in *)sa)->sin_addr);
	ret = snprintf(node, nodelen, "%s", p);
	if (ret < 0 || (size_t)ret >= nodelen) {
		return EAI_MEMORY;
	}
	return 0;
}