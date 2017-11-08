void trace_strbuf(const char *key, const struct strbuf *data)
{
	trace_strbuf_fl(NULL, 0, key, data);
}