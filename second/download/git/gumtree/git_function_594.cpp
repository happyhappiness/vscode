static int packet_write_fmt_1(int fd, int gently,
			      const char *fmt, va_list args)
{
	struct strbuf buf = STRBUF_INIT;
	ssize_t count;

	format_packet(&buf, fmt, args);
	count = write_in_full(fd, buf.buf, buf.len);
	if (count == buf.len)
		return 0;

	if (!gently) {
		check_pipe(errno);
		die_errno("packet write with format failed");
	}
	return error("packet write with format failed");
}