int packet_write_fmt_gently(int fd, const char *fmt, ...)
{
	int status;
	va_list args;

	va_start(args, fmt);
	status = packet_write_fmt_1(fd, 1, fmt, args);
	va_end(args);
	return status;
}