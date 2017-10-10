	int ret = dup(fd);
	if (ret < 0)
		die_errno("dup failed");
	return ret;
}

FILE *xfdopen(int fd, const char *mode)
{
	FILE *stream = fdopen(fd, mode);
	if (stream == NULL)
		die_errno("Out of memory? fdopen failed");
	return stream;
