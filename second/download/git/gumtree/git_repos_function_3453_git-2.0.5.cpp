static void trace_vprintf(const char *key, const char *fmt, va_list ap)
{
	struct strbuf buf = STRBUF_INIT;

	if (!trace_want(key))
		return;

	set_try_to_free_routine(NULL);	/* is never reset */
	strbuf_vaddf(&buf, fmt, ap);
	trace_strbuf(key, &buf);
	strbuf_release(&buf);
}