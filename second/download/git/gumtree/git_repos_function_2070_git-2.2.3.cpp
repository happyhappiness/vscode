ssize_t xpread(int fd, void *buf, size_t len, off_t offset)
{
	ssize_t nr;
	if (len > MAX_IO_SIZE)
		len = MAX_IO_SIZE;
	while (1) {
		nr = pread(fd, buf, len, offset);
		if ((nr < 0) && (errno == EAGAIN || errno == EINTR))
			continue;
		return nr;
	}
}