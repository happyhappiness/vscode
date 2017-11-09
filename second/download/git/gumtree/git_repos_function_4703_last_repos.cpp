void trace_printf(const char *format, ...)
{
	va_list ap;
	va_start(ap, format);
	trace_vprintf_fl(NULL, 0, NULL, format, ap);
	va_end(ap);
}