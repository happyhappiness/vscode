char *git_snpath(char *buf, size_t n, const char *fmt, ...)
{
	char *ret;
	va_list args;
	va_start(args, fmt);
	ret = vsnpath(buf, n, fmt, args);
	va_end(args);
	return ret;
}