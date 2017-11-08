static void lookup_hostname(void)
{
	if (!hostname_lookup_done && hostname) {
#ifndef NO_IPV6
		struct addrinfo hints;
		struct addrinfo *ai;
		int gai;
		static char addrbuf[HOST_NAME_MAX + 1];

		memset(&hints, 0, sizeof(hints));
		hints.ai_flags = AI_CANONNAME;

		gai = getaddrinfo(hostname, NULL, &hints, &ai);
		if (!gai) {
			struct sockaddr_in *sin_addr = (void *)ai->ai_addr;

			inet_ntop(AF_INET, &sin_addr->sin_addr,
				  addrbuf, sizeof(addrbuf));
			free(ip_address);
			ip_address = xstrdup(addrbuf);

			free(canon_hostname);
			canon_hostname = ai->ai_canonname ?
				sanitize_client(ai->ai_canonname) :
				xstrdup(ip_address);

			freeaddrinfo(ai);
		}
#else
		struct hostent *hent;
		struct sockaddr_in sa;
		char **ap;
		static char addrbuf[HOST_NAME_MAX + 1];

		hent = gethostbyname(hostname);
		if (hent) {
			ap = hent->h_addr_list;
			memset(&sa, 0, sizeof sa);
			sa.sin_family = hent->h_addrtype;
			sa.sin_port = htons(0);
			memcpy(&sa.sin_addr, *ap, hent->h_length);

			inet_ntop(hent->h_addrtype, &sa.sin_addr,
				  addrbuf, sizeof(addrbuf));

			free(canon_hostname);
			canon_hostname = sanitize_client(hent->h_name);
			free(ip_address);
			ip_address = xstrdup(addrbuf);
		}
#endif
		hostname_lookup_done = 1;
	}
}