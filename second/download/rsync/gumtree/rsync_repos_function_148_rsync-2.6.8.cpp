void client_sockaddr(int fd,
		     struct sockaddr_storage *ss,
		     socklen_t *ss_len)
{
	memset(ss, 0, sizeof *ss);

	if (getpeername(fd, (struct sockaddr *) ss, ss_len)) {
		/* FIXME: Can we really not continue? */
		rsyserr(FLOG, errno, "getpeername on fd%d failed", fd);
		exit_cleanup(RERR_SOCKETIO);
	}

#ifdef INET6
	if (get_sockaddr_family(ss) == AF_INET6 &&
	    IN6_IS_ADDR_V4MAPPED(&((struct sockaddr_in6 *)ss)->sin6_addr)) {
		/* OK, so ss is in the IPv6 family, but it is really
		 * an IPv4 address: something like
		 * "::ffff:10.130.1.2".  If we use it as-is, then the
		 * reverse lookup might fail or perhaps something else
		 * bad might happen.  So instead we convert it to an
		 * equivalent address in the IPv4 address family.  */
		struct sockaddr_in6 sin6;
		struct sockaddr_in *sin;

		memcpy(&sin6, ss, sizeof sin6);
		sin = (struct sockaddr_in *)ss;
		memset(sin, 0, sizeof *sin);
		sin->sin_family = AF_INET;
		*ss_len = sizeof (struct sockaddr_in);
#ifdef HAVE_SOCKADDR_IN_LEN
		sin->sin_len = *ss_len;
#endif
		sin->sin_port = sin6.sin6_port;

		/* There is a macro to extract the mapped part
		 * (IN6_V4MAPPED_TO_SINADDR ?), but it does not seem
		 * to be present in the Linux headers. */
		memcpy(&sin->sin_addr, &sin6.sin6_addr.s6_addr[12],
		    sizeof sin->sin_addr);
	}
#endif
}