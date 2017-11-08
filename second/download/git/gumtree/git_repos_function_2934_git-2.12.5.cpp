static int packet_write_list(int fd, const char *line, ...)
{
	va_list args;
	int err;
	va_start(args, line);
	for (;;) {
		if (!line)
			break;
		if (strlen(line) > LARGE_PACKET_DATA_MAX)
			return -1;
		err = packet_write_fmt_gently(fd, "%s\n", line);
		if (err)
			return err;
		line = va_arg(args, const char*);
	}
	va_end(args);
	return packet_flush_gently(fd);
}