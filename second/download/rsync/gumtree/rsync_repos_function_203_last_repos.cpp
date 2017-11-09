static int match_address(const char *addr, const char *tok)
{
	char *p;
	struct addrinfo hints, *resa, *rest;
	int gai;
	int ret = 0;
	int addrlen = 0;
#ifdef HAVE_STRTOL
	long int bits;
#else
	int bits;
#endif
	char mask[16];
	char *a = NULL, *t = NULL;

	if (!addr || !*addr)
		return 0;

	p = strchr(tok,'/');
	if (p)
		*p = '\0';

	/* Fail quietly if tok is a hostname, not an address. */
	if (tok[strspn(tok, ".0123456789")] && strchr(tok, ':') == NULL) {
		if (p)
			*p = '/';
		return 0;
	}

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = PF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
#ifdef AI_NUMERICHOST
	hints.ai_flags = AI_NUMERICHOST;
#endif

	if (getaddrinfo(addr, NULL, &hints, &resa) != 0) {
		if (p)
			*p = '/';
		return 0;
	}

	gai = getaddrinfo(tok, NULL, &hints, &rest);
	if (p)
		*p++ = '/';
	if (gai != 0) {
		rprintf(FLOG, "error matching address %s: %s\n",
			tok, gai_strerror(gai));
		freeaddrinfo(resa);
		return 0;
	}

	if (rest->ai_family != resa->ai_family) {
		ret = 0;
		goto out;
	}

	switch(resa->ai_family) {
	case PF_INET:
		a = (char *)&((struct sockaddr_in *)resa->ai_addr)->sin_addr;
		t = (char *)&((struct sockaddr_in *)rest->ai_addr)->sin_addr;
		addrlen = 4;

		break;

#ifdef INET6
	case PF_INET6:
	    {
		struct sockaddr_in6 *sin6a, *sin6t;

		sin6a = (struct sockaddr_in6 *)resa->ai_addr;
		sin6t = (struct sockaddr_in6 *)rest->ai_addr;

		a = (char *)&sin6a->sin6_addr;
		t = (char *)&sin6t->sin6_addr;

		addrlen = 16;

#ifdef HAVE_SOCKADDR_IN6_SCOPE_ID
		if (sin6t->sin6_scope_id &&
		    sin6a->sin6_scope_id != sin6t->sin6_scope_id) {
			ret = 0;
			goto out;
		}
#endif

		break;
	    }
#endif
	default:
	    rprintf(FLOG, "unknown family %u\n", rest->ai_family);
	    ret = 0;
	    goto out;
	}

	bits = -1;
	if (p) {
		if (inet_pton(resa->ai_addr->sa_family, p, mask) <= 0) {
#ifdef HAVE_STRTOL
			char *ep = NULL;
#else
			unsigned char *pp;
#endif

#ifdef HAVE_STRTOL
			bits = strtol(p, &ep, 10);
			if (!*p || *ep) {
				rprintf(FLOG, "malformed mask in %s\n", tok);
				ret = 0;
				goto out;
			}
#else
			for (pp = (unsigned char *)p; *pp; pp++) {
				if (!isascii(*pp) || !isdigit(*pp)) {
					rprintf(FLOG, "malformed mask in %s\n", tok);
					ret = 0;
					goto out;
				}
			}
			bits = atoi(p);
#endif
			if (bits == 0) {
				ret = 1;
				goto out;
			}
			if (bits < 0 || bits > (addrlen << 3)) {
				rprintf(FLOG, "malformed mask in %s\n", tok);
				ret = 0;
				goto out;
			}
		}
	} else {
		bits = 128;
	}

	if (bits >= 0)
		make_mask(mask, bits, addrlen);

	ret = match_binary(a, t, mask, addrlen);

  out:
	freeaddrinfo(resa);
	freeaddrinfo(rest);
	return ret;
}