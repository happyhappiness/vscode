char *xstrfmt(const char *fmt, ...)
{
	va_list ap;
	char *ret;

	va_start(ap, fmt);
	ret = xstrvfmt(fmt, ap);
	va_end(ap);

	return ret;
}