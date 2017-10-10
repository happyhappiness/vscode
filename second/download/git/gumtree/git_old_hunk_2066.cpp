			(int) pktlen - len, line + len + 1);
	if (len && line[len-1] == '\n') {
		line[--len] = 0;
		pktlen--;
	}

	free(hostname);
	free(canon_hostname);
	free(ip_address);
	free(tcp_port);
	hostname = canon_hostname = ip_address = tcp_port = NULL;

	if (len != pktlen)
		parse_host_arg(line + len + 1, pktlen - len - 1);

	for (i = 0; i < ARRAY_SIZE(daemon_service); i++) {
		struct daemon_service *s = &(daemon_service[i]);
		const char *arg;

		if (skip_prefix(line, "git-", &arg) &&
		    skip_prefix(arg, s->name, &arg) &&
		    *arg++ == ' ') {
			/*
			 * Note: The directory here is probably context sensitive,
			 * and might depend on the actual service being performed.
			 */
			return run_service(arg, s);
		}
	}

	logerror("Protocol error: '%s'", line);
	return -1;
}

static int addrcmp(const struct sockaddr_storage *s1,
    const struct sockaddr_storage *s2)
