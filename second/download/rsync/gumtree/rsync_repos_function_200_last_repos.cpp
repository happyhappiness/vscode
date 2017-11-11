static int match_hostname(const char **host_ptr, const char *addr, const char *tok)
{
	struct hostent *hp;
	unsigned int i;
	const char *host = *host_ptr;

	if (!host || !*host)
		return 0;

	/* First check if the reverse-DNS-determined hostname matches. */
	if (iwildmatch(tok, host))
		return 1;

	if (!allow_forward_dns)
		return 0;

	/* Fail quietly if tok is an address or wildcarded entry, not a simple hostname. */
	if (!tok[strspn(tok, ".0123456789")] || tok[strcspn(tok, ":/*?[")])
		return 0;

	/* Now try forward-DNS on the token (config-specified hostname) and see if the IP matches. */
	if (!(hp = gethostbyname(tok)))
		return 0;

	for (i = 0; hp->h_addr_list[i] != NULL; i++) {
		if (strcmp(addr, inet_ntoa(*(struct in_addr*)(hp->h_addr_list[i]))) == 0) {
			/* If reverse lookups are off, we'll use the conf-specified
			 * hostname in preference to UNDETERMINED. */
			if (host == undetermined_hostname) {
				if (!(*host_ptr = strdup(tok)))
					*host_ptr = undetermined_hostname;
			}
			return 1;
		}
	}

	return 0;
}