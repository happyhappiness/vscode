void noop_io_until_death(void)
{
	char buf[1024];

	if (!iobuf.in.buf || !iobuf.out.buf || iobuf.in_fd < 0 || iobuf.out_fd < 0 || kluge_around_eof)
		return;

	kluge_around_eof = 2;
	/* Setting an I/O timeout ensures that if something inexplicably weird
	 * happens, we won't hang around forever. */
	if (!io_timeout)
		set_io_timeout(60);

	while (1)
		read_buf(iobuf.in_fd, buf, sizeof buf);
}