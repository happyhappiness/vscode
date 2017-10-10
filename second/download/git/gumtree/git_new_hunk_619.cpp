		exit(run_builtin(builtin, argc, argv));
	argv_array_clear(&args);
}

static void execv_dashed_external(const char **argv)
{
	struct child_process cmd = CHILD_PROCESS_INIT;
	int status;

	if (get_super_prefix())
		die("%s doesn't support --super-prefix", argv[0]);

	if (use_pager == -1)
		use_pager = check_pager_config(argv[0]);
	commit_pager_choice();

	argv_array_pushf(&cmd.args, "git-%s", argv[0]);
	argv_array_pushv(&cmd.args, argv + 1);
	cmd.clean_on_exit = 1;
	cmd.wait_after_clean = 1;
	cmd.silent_exec_failure = 1;

	trace_argv_printf(cmd.args.argv, "trace: exec:");

	/*
	 * If we fail because the command is not found, it is
	 * OK to return. Otherwise, we just pass along the status code,
	 * or our usual generic code if we were not even able to exec
	 * the program.
	 */
	status = run_command(&cmd);
	if (status >= 0)
		exit(status);
	else if (errno != ENOENT)
		exit(128);
}

static int run_argv(int *argcp, const char ***argv)
{
	int done_alias = 0;

