void packet_write_fmt(int fd, const char *fmt, ...)
{
	va_list args;

	va_start(args, fmt);
	packet_write_fmt_1(fd, 0, fmt, args);
	va_end(args);
}