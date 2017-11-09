static const char *get_trace_prefix(void)
{
	return in_async() ? "sideband" : packet_trace_prefix;
}