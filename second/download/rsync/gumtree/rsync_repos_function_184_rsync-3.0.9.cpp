int compare_addrinfo_sockaddr(const struct addrinfo *ai,
			      const struct sockaddr_storage *ss)
{
	int ss_family = get_sockaddr_family(ss);
	const char fn[] = "compare_addrinfo_sockaddr";

	if (ai->ai_family != ss_family) {
		rprintf(FLOG, "%s: response family %d != %d\n",
			fn, ai->ai_family, ss_family);
		return 1;
	}

	/* The comparison method depends on the particular AF. */
	if (ss_family == AF_INET) {
		const struct sockaddr_in *sin1, *sin2;

		sin1 = (const struct sockaddr_in *) ss;
		sin2 = (const struct sockaddr_in *) ai->ai_addr;

		return memcmp(&sin1->sin_addr, &sin2->sin_addr,
			      sizeof sin1->sin_addr);
	}

#ifdef INET6
	if (ss_family == AF_INET6) {
		const struct sockaddr_in6 *sin1, *sin2;

		sin1 = (const struct sockaddr_in6 *) ss;
		sin2 = (const struct sockaddr_in6 *) ai->ai_addr;

		if (ai->ai_addrlen < sizeof (struct sockaddr_in6)) {
			rprintf(FLOG, "%s: too short sockaddr_in6; length=%d\n",
				fn, (int)ai->ai_addrlen);
			return 1;
		}

		if (memcmp(&sin1->sin6_addr, &sin2->sin6_addr,
			   sizeof sin1->sin6_addr))
			return 1;

#ifdef HAVE_SOCKADDR_IN6_SCOPE_ID
		if (sin1->sin6_scope_id != sin2->sin6_scope_id)
			return 1;
#endif
		return 0;
	}
#endif /* INET6 */

	/* don't know */
	return 1;
}