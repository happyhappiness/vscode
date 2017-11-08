void trace_performance_since(uint64_t start, const char *format, ...)
{
	va_list ap;
	va_start(ap, format);
	trace_performance_vprintf_fl(NULL, 0, getnanotime() - start,
				     format, ap);
	va_end(ap);
}