static int unix_stream_socket(void)
{
	int fd = socket(AF_UNIX, SOCK_STREAM, 0);
	if (fd < 0)
		die_errno("unable to create socket");
	return fd;
}