int unix_stream_connect(const char *path)
{
	int fd, saved_errno;
	struct sockaddr_un sa;
	struct unix_sockaddr_context ctx;

	if (unix_sockaddr_init(&sa, path, &ctx) < 0)
		return -1;
	fd = unix_stream_socket();
	if (connect(fd, (struct sockaddr *)&sa, sizeof(sa)) < 0)
		goto fail;
	unix_sockaddr_cleanup(&ctx);
	return fd;

fail:
	saved_errno = errno;
	unix_sockaddr_cleanup(&ctx);
	close(fd);
	errno = saved_errno;
	return -1;
}