	 * onto stdin/stdout/stderr in the child processes we spawn.
	 */
	sanitize_stdfds();

	git_setup_gettext();

	/*
	 * "git-xxxx" is the same as "git xxxx", but we obviously:
	 *
	 *  - cannot take flags in between the "git" and the "xxxx".
	 *  - cannot execute it externally (since it would just do
	 *    the same thing over again)
	 *
	 * So we just directly call the builtin handler, and die if
	 * that one cannot handle it.
	 */
	if (starts_with(cmd, "git-")) {
		cmd += 4;
		argv[0] = cmd;
		handle_builtin(argc, argv);
		die("cannot handle %s as a builtin", cmd);
	}

	/* Look for flags.. */
	argv++;
	argc--;
	handle_options(&argv, &argc, NULL);
	if (argc > 0) {
		if (starts_with(argv[0], "--"))
			argv[0] += 2;
	} else {
		/* The user didn't specify a command; give them help */
		commit_pager_choice();
		printf("usage: %s\n\n", git_usage_string);
		list_common_cmds_help();
		printf("\n%s\n", _(git_more_info_string));
