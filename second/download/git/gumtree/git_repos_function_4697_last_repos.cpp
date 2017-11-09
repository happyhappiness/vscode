void trace_verbatim(struct trace_key *key, const void *buf, unsigned len)
{
	if (!trace_want(key))
		return;
	trace_write(key, buf, len);
}