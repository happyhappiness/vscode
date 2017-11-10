NORETURN void BUG(const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	BUG_vfl(NULL, 0, fmt, ap);
	va_end(ap);
}