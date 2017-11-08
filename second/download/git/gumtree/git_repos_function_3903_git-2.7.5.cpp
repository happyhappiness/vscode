void trace_verbatim(struct trace_key *key, const void *buf, unsigned len)
{
	if (!trace_want(key))
		return;
	write_or_whine_pipe(get_trace_fd(key), buf, len, err_msg);
}