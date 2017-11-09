void trace_performance_fl(const char *file, int line, uint64_t nanos,
			      const char *format, ...)
{
	va_list ap;
	va_start(ap, format);
	trace_performance_vprintf_fl(file, line, nanos, format, ap);
	va_end(ap);
}