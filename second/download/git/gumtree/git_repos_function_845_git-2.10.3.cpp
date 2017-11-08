int run_command_v_opt_cd_env(const char **argv, int opt, const char *dir, const char *const *env)
{
	struct child_process cmd = CHILD_PROCESS_INIT;
	cmd.argv = argv;
	cmd.no_stdin = opt & RUN_COMMAND_NO_STDIN ? 1 : 0;
	cmd.git_cmd = opt & RUN_GIT_CMD ? 1 : 0;
	cmd.stdout_to_stderr = opt & RUN_COMMAND_STDOUT_TO_STDERR ? 1 : 0;
	cmd.silent_exec_failure = opt & RUN_SILENT_EXEC_FAILURE ? 1 : 0;
	cmd.use_shell = opt & RUN_USING_SHELL ? 1 : 0;
	cmd.clean_on_exit = opt & RUN_CLEAN_ON_EXIT ? 1 : 0;
	cmd.dir = dir;
	cmd.env = env;
	return run_command(&cmd);
}