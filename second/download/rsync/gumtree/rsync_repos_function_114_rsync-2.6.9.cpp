static void mplex_write(enum msgcode code, char *buf, size_t len)
{
	char buffer[1024];
	size_t n = len;

	SIVAL(buffer, 0, ((MPLEX_BASE + (int)code)<<24) + len);

	if (n > sizeof buffer - 4)
		n = 0;
	else
		memcpy(buffer + 4, buf, n);

	writefd_unbuffered(sock_f_out, buffer, n+4);

	len -= n;
	buf += n;

	if (len) {
		defer_forwarding_messages = 1;
		writefd_unbuffered(sock_f_out, buf, len);
		defer_forwarding_messages = 0;
		msg2sndr_flush();
	}
}