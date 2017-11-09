void io_printf(int fd, const char *format, ...)
{
	va_list ap;
	char buf[BIGPATHBUFLEN];
	int len;

	va_start(ap, format);
	len = vsnprintf(buf, sizeof buf, format, ap);
	va_end(ap);

	if (len < 0)
		exit_cleanup(RERR_PROTOCOL);

	if (len >= (int)sizeof buf) {
		rprintf(FERROR, "io_printf() was too long for the buffer.\n");
		exit_cleanup(RERR_PROTOCOL);
	}

	write_sbuf(fd, buf);
}