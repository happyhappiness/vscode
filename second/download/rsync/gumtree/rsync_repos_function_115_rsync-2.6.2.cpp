char *client_addr(int fd)
{
	struct sockaddr_storage ss;
	socklen_t length = sizeof ss;
	char *ssh_client, *p;
	int len;
	static char addr_buf[100];
	static int initialised;

	if (initialised)
		return addr_buf;

	initialised = 1;

	if (am_server) {	/* daemon over --rsh mode */
		strcpy(addr_buf, "0.0.0.0");
		if ((ssh_client = getenv("SSH_CLIENT")) != NULL) {
			/* truncate SSH_CLIENT to just IP address */
			if ((p = strchr(ssh_client, ' ')) != NULL) {
				len = MIN((unsigned int) (p - ssh_client),
				    sizeof addr_buf - 1);
				strncpy(addr_buf, ssh_client, len);
				*(addr_buf + len) = '\0';
			}
		}
	} else {
		client_sockaddr(fd, &ss, &length);
		getnameinfo((struct sockaddr *)&ss, length,
			    addr_buf, sizeof addr_buf, NULL, 0, NI_NUMERICHOST);
	}

	return addr_buf;
}