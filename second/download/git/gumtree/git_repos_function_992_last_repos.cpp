int run_command_v_opt(const char **argv, int opt)
{
	return run_command_v_opt_cd_env(argv, opt, NULL, NULL);
}