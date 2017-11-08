void packet_buf_write(struct strbuf *buf, const char *fmt, ...)
{
	va_list args;
	unsigned n;

	va_start(args, fmt);
	n = format_packet(fmt, args);
	va_end(args);
	strbuf_add(buf, buffer, n);
}