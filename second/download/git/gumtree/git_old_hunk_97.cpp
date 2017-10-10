	git_config(git_default_config, NULL);

	init_revisions(&revs, prefix);
	revs.topo_order = 1;
	revs.show_source = 1;
	revs.rewrite_parents = 1;
	argc = setup_revisions(argc, argv, &revs, NULL);
	argc = parse_options(argc, argv, prefix, options, fast_export_usage, 0);
	if (argc > 1)
		usage_with_options (fast_export_usage, options);

	if (use_done_feature)
		printf("feature done\n");

	if (import_filename)
		import_marks(import_filename);
	lastimportid = last_idnum;
