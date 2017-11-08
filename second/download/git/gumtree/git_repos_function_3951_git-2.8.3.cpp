void trace_printf_key_fl(const char *file, int line, struct trace_key *key,
			 const char *format, ...)
{
	va_list ap;
	va_start(ap, format);
	trace_vprintf_fl(file, line, key, format, ap);
	va_end(ap);
}