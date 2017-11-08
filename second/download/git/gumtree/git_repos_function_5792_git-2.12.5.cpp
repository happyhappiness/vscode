static int print_tool_help(void)
{
	const char *argv[] = { "mergetool", "--tool-help=diff", NULL };
	return run_command_v_opt(argv, RUN_GIT_CMD);
}