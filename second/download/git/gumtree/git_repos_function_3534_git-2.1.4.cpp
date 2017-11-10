void trace_command_performance(const char **argv)
{
	if (!trace_want(&trace_perf_key))
		return;

	if (!command_start_time)
		atexit(print_command_performance_atexit);

	strbuf_reset(&command_line);
	sq_quote_argv(&command_line, argv, 0);
	command_start_time = getnanotime();
}