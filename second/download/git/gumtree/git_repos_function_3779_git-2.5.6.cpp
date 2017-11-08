void trace_argv_printf(const char **argv, const char *format, ...)
{
	va_list ap;
	va_start(ap, format);
	trace_argv_vprintf_fl(NULL, 0, argv, format, ap);
	va_end(ap);
}