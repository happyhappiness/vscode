static void print_command_performance_atexit(void)
{
	trace_performance_since(command_start_time, "git command:%s",
				command_line.buf);
}