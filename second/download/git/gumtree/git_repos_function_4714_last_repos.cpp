int trace_want(struct trace_key *key)
{
	return !!get_trace_fd(key);
}