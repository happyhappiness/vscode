		if ((nr < 0) && (errno == EAGAIN || errno == EINTR))
			continue;
		return nr;
	}
}

/*
 * xpread() is the same as pread(), but it automatically restarts pread()
 * operations with a recoverable error (EAGAIN and EINTR). xpread() DOES
 * NOT GUARANTEE that "len" bytes is read even if the data is available.
 */
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

ssize_t read_in_full(int fd, void *buf, size_t count)
{
	char *p = buf;
	ssize_t total = 0;

	while (count > 0) {
