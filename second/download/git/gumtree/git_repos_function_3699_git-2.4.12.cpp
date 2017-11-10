void trace_performance(uint64_t nanos, const char *format, ...)
{
	va_list ap;
	va_start(ap, format);
	trace_performance_vprintf_fl(NULL, 0, nanos, format, ap);
	va_end(ap);
}