static void report(const char *fmt, ...)
{
	va_list vp;

	if (!verbose)
		return;

	va_start(vp, fmt);
	vprintf(fmt, vp);
	putchar('\n');
	va_end(vp);
}