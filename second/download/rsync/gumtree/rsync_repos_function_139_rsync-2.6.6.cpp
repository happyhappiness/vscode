char *client_addr(int fd)
{
	static char addr_buf[100];
	static int initialised;
	struct sockaddr_storage ss;
	socklen_t length = sizeof ss;
	char *ssh_info, *p;

	if (initialised)
		return addr_buf;

	initialised = 1;

	if (am_server) {	/* daemon over --rsh mode */
		strcpy(addr_buf, "0.0.0.0");
		if ((ssh_info = getenv("SSH_CONNECTION")) != NULL
		    || (ssh_info = getenv("SSH_CLIENT")) != NULL
		    || (ssh_info = getenv("SSH2_CLIENT")) != NULL) {
			strlcpy(addr_buf, ssh_info, sizeof addr_buf);
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