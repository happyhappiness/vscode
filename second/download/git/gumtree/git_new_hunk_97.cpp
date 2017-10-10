	git_config(git_default_config, NULL);

	init_revisions(&revs, prefix);
	revs.topo_order = 1;
	revs.show_source = 1;
	revs.rewrite_parents = 1;
	argc = parse_options(argc, argv, prefix, options, fast_export_usage,
			PARSE_OPT_KEEP_ARGV0 | PARSE_OPT_KEEP_UNKNOWN);
	argc = setup_revisions(argc, argv, &revs, NULL);
	if (argc > 1)
		usage_with_options (fast_export_usage, options);

	if (refspecs_list.nr) {
		const char **refspecs_str;
		int i;

		refspecs_str = xmalloc(sizeof(*refspecs_str) * refspecs_list.nr);
		for (i = 0; i < refspecs_list.nr; i++)
			refspecs_str[i] = refspecs_list.items[i].string;

		refspecs_nr = refspecs_list.nr;
		refspecs = parse_fetch_refspec(refspecs_nr, refspecs_str);

		string_list_clear(&refspecs_list, 1);
		free(refspecs_str);
	}

	if (use_done_feature)
		printf("feature done\n");

	if (import_filename)
		import_marks(import_filename);
	lastimportid = last_idnum;
