char *client_addr(int fd)
{
	struct sockaddr_storage ss;
	socklen_t length = sizeof ss;
	static char addr_buf[100];
	static int initialised;

	if (initialised) return addr_buf;

	initialised = 1;

	client_sockaddr(fd, &ss, &length);

	getnameinfo((struct sockaddr *)&ss, length,
		    addr_buf, sizeof(addr_buf), NULL, 0, NI_NUMERICHOST);
	
	return addr_buf;
}