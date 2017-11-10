void trace_printf_key(struct trace_key *key, const char *format, ...)
{
	va_list ap;
	va_start(ap, format);
	trace_vprintf_fl(NULL, 0, key, format, ap);
	va_end(ap);
}