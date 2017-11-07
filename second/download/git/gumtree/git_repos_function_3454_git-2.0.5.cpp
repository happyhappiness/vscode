void trace_printf_key(const char *key, const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	trace_vprintf(key, fmt, ap);
	va_end(ap);
}