ssize_t xwrite(int fd, const void *buf, size_t len)
{
	ssize_t nr;
	if (len > MAX_IO_SIZE)
	    len = MAX_IO_SIZE;
	while (1) {
		nr = write(fd, buf, len);
		if ((nr < 0) && (errno == EAGAIN || errno == EINTR))
			continue;
		return nr;
	}
}