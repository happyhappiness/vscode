static int test_vsnprintf(const char *fmt, ...)
{
	char buf[26];
	int ret;
	va_list ap;
	va_start(ap, fmt);
	ret = vsnprintf(buf, sizeof(buf), fmt, ap);
	va_end(ap);
	return ret;
}