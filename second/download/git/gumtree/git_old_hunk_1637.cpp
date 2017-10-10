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
