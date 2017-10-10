	return write_archive(sent_argv.argc, sent_argv.argv, prefix, 0, NULL, 1);
}

__attribute__((format (printf, 1, 2)))
static void error_clnt(const char *fmt, ...)
{
	char buf[1024];
	va_list params;
	int len;

	va_start(params, fmt);
	len = vsprintf(buf, fmt, params);
	va_end(params);
	send_sideband(1, 3, buf, len, LARGE_PACKET_MAX);
	die("sent error to the client: %s", buf);
}

static ssize_t process_input(int child_fd, int band)
{
	char buf[16384];
	ssize_t sz = read(child_fd, buf, sizeof(buf));
