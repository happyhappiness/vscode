int read_line_old(int fd, char *buf, size_t bufsiz, int eof_ok)
{
	assert(fd != iobuf.in_fd);
	bufsiz--; /* leave room for the null */
	while (bufsiz > 0) {
		if (safe_read(fd, buf, 1) == 0) {
			if (eof_ok)
				break;
			return 0;
		}
		if (*buf == '\0')
			return 0;
		if (*buf == '\n')
			break;
		if (*buf != '\r') {
			buf++;
			bufsiz--;
		}
	}
	*buf = '\0';
	return bufsiz > 0;
}