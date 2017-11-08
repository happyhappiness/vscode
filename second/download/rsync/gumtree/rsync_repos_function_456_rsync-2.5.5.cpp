int
getnameinfo(sa, salen, host, hostlen, serv, servlen, flags)
	const struct sockaddr *sa;
	size_t salen;
	char *host;
	size_t hostlen;
	char *serv;
	size_t servlen;
	int flags;
{
	extern int h_errno;
	struct afd *afd;
	struct servent *sp;
	struct hostent *hp;
	u_short port;
	int family, i;
	char *addr, *p;
	u_long v4a;
	u_char pfx;
	int h_error;
	char numserv[512];
	char numaddr[512];

	if (sa == NULL)
		return ENI_NOSOCKET;

#ifdef HAVE_SOCKADDR_LEN
	if (sa->sa_len != salen) return ENI_SALEN;
#endif /* HAVE_SOCKADDR_LEN */
	
	family = sa->sa_family;
	for (i = 0; afdl[i].a_af; i++)
		if (afdl[i].a_af == family) {
			afd = &afdl[i];
			goto found;
		}
	return ENI_FAMILY;
	
 found:
	if (salen != afd->a_socklen) return ENI_SALEN;
	
	port = ((struct sockinet *)sa)->si_port; /* network byte order */
	addr = (char *)sa + afd->a_off;

	if (serv == NULL || servlen == 0) {
		/* what we should do? */
	} else if (flags & NI_NUMERICSERV) {
		snprintf(numserv, sizeof(numserv), "%d", ntohs(port));
		if (strlen(numserv) > servlen)
			return ENI_MEMORY;
		strcpy(serv, numserv);
	} else {
		sp = getservbyport(port, (flags & NI_DGRAM) ? "udp" : "tcp");
		if (sp) {
			if (strlen(sp->s_name) > servlen)
				return ENI_MEMORY;
			strcpy(serv, sp->s_name);
		} else
			return ENI_NOSERVNAME;
	}

	switch (sa->sa_family) {
	case AF_INET:
		v4a = ((struct sockaddr_in *)sa)->sin_addr.s_addr;
		if (IN_MULTICAST(v4a) || IN_EXPERIMENTAL(v4a))
			flags |= NI_NUMERICHOST;
		v4a >>= IN_CLASSA_NSHIFT;
		if (v4a == 0 || v4a == IN_LOOPBACKNET)
			flags |= NI_NUMERICHOST;			
		break;
#ifdef INET6
	case AF_INET6:
		pfx = ((struct sockaddr_in6 *)sa)->sin6_addr.s6_addr[0];
		if (pfx == 0 || pfx == 0xfe || pfx == 0xff)
			flags |= NI_NUMERICHOST;
		break;
#endif
	}
	if (host == NULL || hostlen == 0) {
		/* what should we do? */
	} else if (flags & NI_NUMERICHOST) {
		if (!inet_ntop(afd->a_af, addr, numaddr, sizeof(numaddr)))
			return ENI_SYSTEM;
		if (strlen(numaddr) > hostlen)
			return ENI_MEMORY;
		strcpy(host, numaddr);
	} else {
#ifdef INET6
		hp = getipnodebyaddr(addr, afd->a_addrlen, afd->a_af, &h_error);
#else
		hp = gethostbyaddr(addr, afd->a_addrlen, afd->a_af);
		h_error = h_errno;
#endif

		if (hp) {
			if (flags & NI_NOFQDN) {
				p = strchr(hp->h_name, '.');
				if (p) *p = '\0';
			}
			if (strlen(hp->h_name) > hostlen) {
#ifdef INET6
				freehostent(hp);
#endif
				return ENI_MEMORY;
			}
			strcpy(host, hp->h_name);
#ifdef INET6
			freehostent(hp);
#endif
		} else {
			if (flags & NI_NAMEREQD)
				return ENI_NOHOSTNAME;
			if (!inet_ntop(afd->a_af, addr, numaddr, sizeof(numaddr)))
				return ENI_NOHOSTNAME;
			if (strlen(numaddr) > hostlen)
				return ENI_MEMORY;
			strcpy(host, numaddr);
		}
	}
	return SUCCESS;
}