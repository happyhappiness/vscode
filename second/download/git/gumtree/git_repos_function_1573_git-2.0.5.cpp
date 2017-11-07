static int write_buffer(int fd, const void *buf, size_t len)
{
	if (write_in_full(fd, buf, len) < 0)
		return error("file write error (%s)", strerror(errno));
	return 0;
}