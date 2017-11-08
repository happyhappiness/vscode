int run_command_v_opt_cd_env(const char **argv, int opt, const char *dir, const char *const *env)
{
	struct child_process cmd;
	prepare_run_command_v_opt(&cmd, argv, opt);
	cmd.dir = dir;
	cmd.env = env;
	return run_command(&cmd);
}