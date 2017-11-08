static void read_error_fd(void)
{
	char buf[200];
	size_t n;
	int fd = io_error_fd;
	int tag, len;

	/* io_error_fd is temporarily disabled -- is this meant to
	 * prevent indefinite recursion? */
	io_error_fd = -1;

	read_loop(fd, buf, 4);
	tag = IVAL(buf, 0);

	len = tag & 0xFFFFFF;
	tag = tag >> 24;
	tag -= MPLEX_BASE;

	while (len) {
		n = len;
		if (n > (sizeof buf - 1))
			n = sizeof buf - 1;
		read_loop(fd, buf, n);
		rwrite((enum logcode)tag, buf, n);
		len -= n;
	}

	io_error_fd = fd;
}