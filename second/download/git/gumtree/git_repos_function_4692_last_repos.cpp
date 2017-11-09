static void normalize_trace_key(struct trace_key **key)
{
	static struct trace_key trace_default = { "GIT_TRACE" };
	if (!*key)
		*key = &trace_default;
}