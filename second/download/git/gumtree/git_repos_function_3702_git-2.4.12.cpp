void trace_argv_printf_fl(const char *file, int line, const char **argv,
			  const char *format, ...)
{
	va_list ap;
	va_start(ap, format);
	trace_argv_vprintf_fl(file, line, argv, format, ap);
	va_end(ap);
}