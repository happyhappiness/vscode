	/* No need to check if there are no submodules configured */
	if (!submodule_from_path(NULL, NULL))
		return;

	init_revisions(&rev, NULL);
	argv_array_push(&argv, "--"); /* argv[0] program name */
	oid_array_for_each_unique(&ref_tips_after_fetch,
				   add_oid_to_argv, &argv);
	argv_array_push(&argv, "--not");
	oid_array_for_each_unique(&ref_tips_before_fetch,
				   add_oid_to_argv, &argv);
	setup_revisions(argv.argc, argv.argv, &rev, NULL);
	if (prepare_revision_walk(&rev))
		die("revision walk setup failed");

	/*
	 * Collect all submodules (whether checked out or not) for which new
