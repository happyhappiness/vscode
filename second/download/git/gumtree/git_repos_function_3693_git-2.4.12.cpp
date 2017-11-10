void trace_strbuf_fl(const char *file, int line, struct trace_key *key,
		     const struct strbuf *data)
{
	struct strbuf buf = STRBUF_INIT;

	if (!prepare_trace_line(file, line, key, &buf))
		return;

	strbuf_addbuf(&buf, data);
	print_trace_line(key, &buf);
}