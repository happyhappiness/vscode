static int update_submodules(void)
{
	struct child_process cp = CHILD_PROCESS_INIT;

	cp.git_cmd = 1;
	cp.no_stdin = 1;
	argv_array_pushl(&cp.args, "submodule", "update",
				   "--recursive", "--checkout", NULL);

	return run_command(&cp);
}