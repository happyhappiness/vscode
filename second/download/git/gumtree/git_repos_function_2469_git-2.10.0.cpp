void fprintf_or_die(FILE *f, const char *fmt, ...)
{
	va_list ap;
	int ret;

	va_start(ap, fmt);
	ret = vfprintf(f, fmt, ap);
	va_end(ap);

	if (ret < 0) {
		check_pipe(errno);
		die_errno("write error");
	}
}