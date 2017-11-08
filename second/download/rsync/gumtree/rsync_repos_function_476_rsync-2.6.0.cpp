static int
get_addr(hostname, af, res, pai, port0)
	const char *hostname;
	int af;
	struct addrinfo **res;
	struct addrinfo *pai;
	int port0;
{
	u_short port = port0 & 0xffff;
	struct addrinfo sentinel;
	struct hostent *hp;
	struct addrinfo *top, *cur;
	struct afd *afd;
	int i, error = 0, h_error;
	char *ap;
#ifndef INET6
	extern int h_errno;
#endif

	top = NULL;
	sentinel.ai_next = NULL;
	cur = &sentinel;
#ifdef INET6
	if (af == AF_UNSPEC) {
		hp = getipnodebyname(hostname, AF_INET6,
				AI_ADDRCONFIG|AI_ALL|AI_V4MAPPED, &h_error);
	} else
		hp = getipnodebyname(hostname, af, AI_ADDRCONFIG, &h_error);
#else
	hp = gethostbyname(hostname);
	h_error = h_errno;
#endif
	if (hp == NULL) {
		switch (h_error) {
		case HOST_NOT_FOUND:
		case NO_DATA:
			error = EAI_NODATA;
			break;
		case TRY_AGAIN:
			error = EAI_AGAIN;
			break;
		case NO_RECOVERY:
		default:
			error = EAI_FAIL;
			break;
		}
		goto bad;
	}

	if ((hp->h_name == NULL) || (hp->h_name[0] == 0) ||
	    (hp->h_addr_list[0] == NULL))
		ERR(EAI_FAIL);
	
	for (i = 0; (ap = hp->h_addr_list[i]) != NULL; i++) {
		switch (af) {
#ifdef INET6
		case AF_INET6:
			afd = &afdl[N_INET6];
			break;
#endif
#ifndef INET6
		default:	/* AF_UNSPEC */
#endif
		case AF_INET:
			afd = &afdl[N_INET];
			break;
#ifdef INET6
		default:	/* AF_UNSPEC */
			if (IN6_IS_ADDR_V4MAPPED((struct in6_addr *)ap)) {
				ap += sizeof(struct in6_addr) -
					sizeof(struct in_addr);
				afd = &afdl[N_INET];
			} else
				afd = &afdl[N_INET6];
			break;
#endif
		}
#ifdef FAITH
		if (translate && afd->a_af == AF_INET) {
			struct in6_addr *in6;

			if (!get_ai(&cur->ai_next, pai, &afdl[N_INET6], ap, port))
				goto free;
			in6 = &((struct sockaddr_in6 *)cur->ai_next->ai_addr)->sin6_addr;
			memcpy(&in6->s6_addr32[0], &faith_prefix,
			    sizeof(struct in6_addr) - sizeof(struct in_addr));
			memcpy(&in6->s6_addr32[3], ap, sizeof(struct in_addr));
		} else
#endif /* FAITH */
		if (!get_ai(&cur->ai_next, pai, afd, ap, port))
			goto free;
		if (cur == &sentinel) {
			top = cur->ai_next;
			GET_CANONNAME(top, hp->h_name);
		}
		cur = cur->ai_next;
	}
#ifdef INET6
	freehostent(hp);
#endif
	*res = top;
	return SUCCESS;
 free:
	if (top)
		freeaddrinfo(top);
#ifdef INET6
	if (hp)
		freehostent(hp);
#endif
 bad:
	*res = NULL;
	return error;
}