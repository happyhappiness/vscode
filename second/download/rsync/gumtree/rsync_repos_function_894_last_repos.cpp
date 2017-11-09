static int getservicenameinfo(const struct sockaddr *sa,
			char *service,
			size_t servicelen,
			int flags)
{
	int ret = -1;
	int port = ntohs(((struct sockaddr_in *)sa)->sin_port);

	if (!(flags & NI_NUMERICSERV)) {
		struct servent *se = getservbyport(
				port,
				(flags & NI_DGRAM) ? "udp" : "tcp");
		if (se && se->s_name) {
			/* Service name looked up successfully. */
			ret = snprintf(service, servicelen, "%s", se->s_name);
			if (ret < 0 || (size_t)ret >= servicelen) {
				return EAI_MEMORY;
			}
			return 0;
		}
		/* Otherwise just fall into the numeric service code... */
	}
	ret = snprintf(service, servicelen, "%d", port);
	if (ret < 0 || (size_t)ret >= servicelen) {
		return EAI_MEMORY;
	}
	return 0;
}