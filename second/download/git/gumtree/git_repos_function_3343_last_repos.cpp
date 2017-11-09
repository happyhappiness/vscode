static void format_write(int fd, const char *fmt, ...)
{
	static char buffer[1024];

	va_list args;
	unsigned n;

	va_start(args, fmt);
	n = vsnprintf(buffer, sizeof(buffer), fmt, args);
	va_end(args);
	if (n >= sizeof(buffer))
		die("protocol error: impossibly long line");

	write_or_die(fd, buffer, n);
}