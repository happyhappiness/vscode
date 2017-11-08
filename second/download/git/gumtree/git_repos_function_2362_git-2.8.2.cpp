ssize_t xread(int fd, void *buf, size_t len)
{
	ssize_t nr;
	if (len > MAX_IO_SIZE)
	    len = MAX_IO_SIZE;
	while (1) {
		nr = read(fd, buf, len);
		if (nr < 0) {
			if (errno == EINTR)
				continue;
			if (errno == EAGAIN || errno == EWOULDBLOCK) {
				struct pollfd pfd;
				pfd.events = POLLIN;
				pfd.fd = fd;
				/*
				 * it is OK if this poll() failed; we
				 * want to leave this infinite loop
				 * only when read() returns with
				 * success, or an expected failure,
				 * which would be checked by the next
				 * call to read(2).
				 */
				poll(&pfd, 1, -1);
			}
		}
		return nr;
	}
}