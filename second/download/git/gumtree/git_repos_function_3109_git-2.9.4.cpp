static void lookup_hostname(struct hostinfo *hi)
{
	if (!hi->hostname_lookup_done && hi->hostname.len) {
#ifndef NO_IPV6
		struct addrinfo hints;
		struct addrinfo *ai;
		int gai;
		static char addrbuf[HOST_NAME_MAX + 1];

		memset(&hints, 0, sizeof(hints));
		hints.ai_flags = AI_CANONNAME;

		gai = getaddrinfo(hi->hostname.buf, NULL, &hints, &ai);
		if (!gai) {
			struct sockaddr_in *sin_addr = (void *)ai->ai_addr;

			inet_ntop(AF_INET, &sin_addr->sin_addr,
				  addrbuf, sizeof(addrbuf));
			strbuf_addstr(&hi->ip_address, addrbuf);

			if (ai->ai_canonname)
				sanitize_client(&hi->canon_hostname,
						ai->ai_canonname);
			else
				strbuf_addbuf(&hi->canon_hostname,
					      &hi->ip_address);

			freeaddrinfo(ai);
		}
#else
		struct hostent *hent;
		struct sockaddr_in sa;
		char **ap;
		static char addrbuf[HOST_NAME_MAX + 1];

		hent = gethostbyname(hi->hostname.buf);
		if (hent) {
			ap = hent->h_addr_list;
			memset(&sa, 0, sizeof sa);
			sa.sin_family = hent->h_addrtype;
			sa.sin_port = htons(0);
			memcpy(&sa.sin_addr, *ap, hent->h_length);

			inet_ntop(hent->h_addrtype, &sa.sin_addr,
				  addrbuf, sizeof(addrbuf));

			sanitize_client(&hi->canon_hostname, hent->h_name);
			strbuf_addstr(&hi->ip_address, addrbuf);
		}
#endif
		hi->hostname_lookup_done = 1;
	}
}