char *client_name(int fd)
{
	static char name_buf[100];
	static char port_buf[100];
	static int initialised;
	struct sockaddr_storage ss, *ssp;
	struct sockaddr_in sin;
#ifdef INET6
	struct sockaddr_in6 sin6;
#endif
	socklen_t ss_len;

	if (initialised) return name_buf;

	strcpy(name_buf, default_name);
	initialised = 1;

	if (am_server) {
		/* daemon over --rsh mode */

		char *addr = client_addr(fd);
#ifdef INET6
		int dots = 0;
		char *p;

		for (p = addr; *p && (dots <= 3); p++) {
		    if (*p == '.')
			dots++;
		}
		if (dots > 3) {
			/* more than 4 parts to IP address, must be ipv6 */
			ssp = (struct sockaddr_storage *) &sin6;
			ss_len = sizeof sin6;
			memset(ssp, 0, ss_len);
			inet_pton(AF_INET6, addr, &sin6.sin6_addr);
			sin6.sin6_family = AF_INET6;
		} else
#endif
		{
			ssp = (struct sockaddr_storage *) &sin;
			ss_len = sizeof sin;
			memset(ssp, 0, ss_len);
			inet_pton(AF_INET, addr, &sin.sin_addr);
			sin.sin_family = AF_INET;
		}

	} else {
		ss_len = sizeof ss;
		ssp = &ss;

		client_sockaddr(fd, &ss, &ss_len);

	}

	if (!lookup_name(fd, ssp, ss_len, name_buf, sizeof name_buf, 
			port_buf, sizeof port_buf))
		check_name(fd, ssp, name_buf);

	return name_buf;
}