char *client_name(int fd)
{
	struct sockaddr_storage ss;
	socklen_t ss_len = sizeof ss;
	static char name_buf[100];
	static char port_buf[100];
	static int initialised;

	if (initialised) return name_buf;

	strcpy(name_buf, default_name);
	initialised = 1;

	client_sockaddr(fd, &ss, &ss_len);

	if (!lookup_name(fd, &ss, ss_len, name_buf, sizeof name_buf, port_buf, sizeof port_buf))
		check_name(fd, &ss, name_buf, port_buf);

	return name_buf;
}