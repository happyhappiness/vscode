static void mplex_write(enum msgcode code, char *buf, size_t len)
{
	char buffer[4096];
	size_t n = len;

	SIVAL(buffer, 0, ((MPLEX_BASE + (int)code)<<24) + len);

	/* When the generator reads messages from the msg_fd_in pipe, it can
	 * cause output to occur down the socket.  Setting contiguous_write_len
	 * prevents the reading of msg_fd_in once we actually start to write
	 * this sequence of data (though we might read it before the start). */
	if (am_generator && msg_fd_in >= 0)
		contiguous_write_len = len + 4;

	if (n > sizeof buffer - 4)
		n = sizeof buffer - 4;

	memcpy(&buffer[4], buf, n);
	writefd_unbuffered(sock_f_out, buffer, n+4);

	len -= n;
	buf += n;

	if (len)
		writefd_unbuffered(sock_f_out, buf, len);

	if (am_generator && msg_fd_in >= 0)
		contiguous_write_len = 0;
}