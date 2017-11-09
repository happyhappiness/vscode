int printf_ln(const char *fmt, ...)
{
	int ret;
	va_list ap;
	va_start(ap, fmt);
	ret = vprintf(fmt, ap);
	va_end(ap);
	if (ret < 0 || putchar('\n') == EOF)
		return -1;
	return ret + 1;
}