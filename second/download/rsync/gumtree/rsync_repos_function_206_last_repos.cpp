char *client_addr(int fd)
{
	static char addr_buf[100];
	static int initialised;
	struct sockaddr_storage ss;
	socklen_t length = sizeof ss;

	if (initialised)
		return addr_buf;

	initialised = 1;

	if (am_server) {	/* daemon over --rsh mode */
		char *env_str;
		strlcpy(addr_buf, "0.0.0.0", sizeof addr_buf);
		if ((env_str = getenv("REMOTE_HOST")) != NULL
		 || (env_str = getenv("SSH_CONNECTION")) != NULL
		 || (env_str = getenv("SSH_CLIENT")) != NULL
		 || (env_str = getenv("SSH2_CLIENT")) != NULL) {
			char *p;
			strlcpy(addr_buf, env_str, sizeof addr_buf);
			/* Truncate the value to just the IP address. */
			if ((p = strchr(addr_buf, ' ')) != NULL)
				*p = '\0';
		}
	} else {
		client_sockaddr(fd, &ss, &length);
		getnameinfo((struct sockaddr *)&ss, length,
			    addr_buf, sizeof addr_buf, NULL, 0, NI_NUMERICHOST);
	}

	return addr_buf;
}