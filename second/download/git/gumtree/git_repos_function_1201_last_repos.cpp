const char *split_cmdline_strerror(int split_cmdline_errno)
{
	return split_cmdline_errors[-split_cmdline_errno - 1];
}