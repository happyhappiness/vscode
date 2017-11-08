int fprintf_ln(FILE *fp, const char *fmt, ...)
{
	int ret;
	va_list ap;
	va_start(ap, fmt);
	ret = vfprintf(fp, fmt, ap);
	va_end(ap);
	if (ret < 0 || putc('\n', fp) == EOF)
		return -1;
	return ret + 1;
}