void packet_buf_write(struct strbuf *buf, const char *fmt, ...)
{
	va_list args;

	va_start(args, fmt);
	format_packet(buf, fmt, args);
	va_end(args);
}