static int
get_name(addr, afd, res, numaddr, pai, port0)
	const char *addr;
	struct afd *afd;
	struct addrinfo **res;
	char *numaddr;
	struct addrinfo *pai;
	int port0;
{
	u_short port = port0 & 0xffff;
	struct hostent *hp;
	struct addrinfo *cur;
	int error = 0;
	
#ifdef INET6
	{
		int h_error;
		hp = getipnodebyaddr(addr, afd->a_addrlen, afd->a_af, &h_error);
	}
#else
	hp = gethostbyaddr(addr, afd->a_addrlen, AF_INET);
#endif
	if (hp && hp->h_name && hp->h_name[0] && hp->h_addr_list[0]) {
		if (!get_ai(&cur, pai, afd, hp->h_addr_list[0], port))
			goto free;
		GET_CANONNAME(cur, hp->h_name);
	} else {
		if (!get_ai(&cur, pai, afd, numaddr, port))
			goto free;
	}
	
#ifdef INET6
	if (hp)
		freehostent(hp);
#endif
	*res = cur;
	return SUCCESS;
 free:
	if (cur)
		freeaddrinfo(cur);
#ifdef INET6
	if (hp)
		freehostent(hp);
#endif
 /* bad: */
	*res = NULL;
	return error;
}