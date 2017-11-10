void trace_strbuf(struct trace_key *key, const struct strbuf *data)
{
	trace_strbuf_fl(NULL, 0, key, data);
}