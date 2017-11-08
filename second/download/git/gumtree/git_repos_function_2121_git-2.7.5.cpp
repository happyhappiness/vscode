int unix_stream_listen(const char *path)
{
	int fd, saved_errno;
	struct sockaddr_un sa;
	struct unix_sockaddr_context ctx;

	unlink(path);

	if (unix_sockaddr_init(&sa, path, &ctx) < 0)
		return -1;
	fd = unix_stream_socket();

	if (bind(fd, (struct sockaddr *)&sa, sizeof(sa)) < 0)
		goto fail;

	if (listen(fd, 5) < 0)
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