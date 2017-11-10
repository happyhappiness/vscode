static void trace_performance_vprintf_fl(const char *file, int line,
					 uint64_t nanos, const char *format,
					 va_list ap)
{
	struct strbuf buf = STRBUF_INIT;

	if (!prepare_trace_line(file, line, &trace_perf_key, &buf))
		return;

	strbuf_addf(&buf, "performance: %.9f s", (double) nanos / 1000000000);

	if (format && *format) {
		strbuf_addstr(&buf, ": ");
		strbuf_vaddf(&buf, format, ap);
	}

	print_trace_line(&trace_perf_key, &buf);
}