NORETURN void BUG_fl(const char *file, int line, const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	BUG_vfl(file, line, fmt, ap);
	va_end(ap);
}