void trace_printf(const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	trace_vprintf("GIT_TRACE", fmt, ap);
	va_end(ap);
}