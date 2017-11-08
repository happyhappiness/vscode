void vwritef(int fd, const char *prefix, const char *err, va_list params)
{
	char msg[4096];
	int len = vsnprintf(msg, sizeof(msg), err, params);
	if (len > sizeof(msg))
		len = sizeof(msg);

	write_in_full(fd, prefix, strlen(prefix));
	write_in_full(fd, msg, len);
	write_in_full(fd, "\n", 1);
}