ssize_t xwrite(int fd, const void *buf, size_t len)
{
	ssize_t nr;
	if (len > MAX_IO_SIZE)
	    len = MAX_IO_SIZE;
	while (1) {
		nr = write(fd, buf, len);
		if (nr < 0) {
			if (errno == EINTR)
				continue;
			if (handle_nonblock(fd, POLLOUT, errno))
				continue;
		}

		return nr;
	}
}