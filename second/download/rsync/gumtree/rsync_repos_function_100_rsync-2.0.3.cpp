char *client_addr(int fd)
{
	struct sockaddr sa;
	struct sockaddr_in *sockin = (struct sockaddr_in *) (&sa);
	int     length = sizeof(sa);
	static char addr_buf[100];

	if (getpeername(fd, &sa, &length)) {
		exit(1);
	}

	strlcpy(addr_buf,(char *)inet_ntoa(sockin->sin_addr), sizeof(addr_buf)-1);

	return addr_buf;
}