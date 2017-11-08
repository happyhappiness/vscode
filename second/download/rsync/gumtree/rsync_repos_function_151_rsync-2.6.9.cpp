int check_name(int fd,
	       const struct sockaddr_storage *ss,
	       char *name_buf, size_t name_buf_size)
{
	struct addrinfo hints, *res, *res0;
	int error;
	int ss_family = get_sockaddr_family(ss);

	memset(&hints, 0, sizeof hints);
	hints.ai_family = ss_family;
	hints.ai_flags = AI_CANONNAME;
	hints.ai_socktype = SOCK_STREAM;
	error = getaddrinfo(name_buf, NULL, &hints, &res0);
	if (error) {
		rprintf(FLOG, "forward name lookup for %s failed: %s\n",
			name_buf, gai_strerror(error));
		strlcpy(name_buf, default_name, name_buf_size);
		return error;
	}

	/* Given all these results, we expect that one of them will be
	 * the same as ss.  The comparison is a bit complicated. */
	for (res = res0; res; res = res->ai_next) {
		if (!compare_addrinfo_sockaddr(res, ss))
			break;	/* OK, identical */
	}

	if (!res0) {
		/* We hit the end of the list without finding an
		 * address that was the same as ss. */
		rprintf(FLOG, "no known address for \"%s\": "
			"spoofed address?\n", name_buf);
		strlcpy(name_buf, default_name, name_buf_size);
	} else if (res == NULL) {
		/* We hit the end of the list without finding an
		 * address that was the same as ss. */
		rprintf(FLOG, "%s is not a known address for \"%s\": "
			"spoofed address?\n", client_addr(fd), name_buf);
		strlcpy(name_buf, default_name, name_buf_size);
	}

	freeaddrinfo(res0);
	return 0;
}