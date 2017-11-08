static void trace_argv_vprintf_fl(const char *file, int line,
				  const char **argv, const char *format,
				  va_list ap)
{
	struct strbuf buf = STRBUF_INIT;

	if (!prepare_trace_line(file, line, NULL, &buf))
		return;

	strbuf_vaddf(&buf, format, ap);

	sq_quote_argv(&buf, argv, 0);
	print_trace_line(NULL, &buf);
}