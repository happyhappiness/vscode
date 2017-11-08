int run_command_v_opt(const char **argv, int opt)
{
	struct child_process cmd;
	prepare_run_command_v_opt(&cmd, argv, opt);
	return run_command(&cmd);
}