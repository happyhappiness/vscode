	 * environment, and the $(gitexecdir) from the Makefile at build
	 * time.
	 */
	setup_path();

	while (1) {
		int was_alias = run_argv(&argc, &argv);
		if (errno != ENOENT)
			break;
		if (was_alias) {
			fprintf(stderr, "Expansion of alias '%s' failed; "
				"'%s' is not a git command\n",
				cmd, argv[0]);
