			     N_("field name to sort on"), &parse_opt_ref_sorting),
		{
			OPTION_CALLBACK, 0, "points-at", &filter.points_at, N_("object"),
			N_("print only branches of the object"), 0, parse_opt_object_name
		},
		OPT_BOOL('i', "ignore-case", &icase, N_("sorting and filtering are case insensitive")),
		OPT_END(),
	};

	memset(&filter, 0, sizeof(filter));
	filter.kind = FILTER_REFS_BRANCHES;
	filter.abbrev = -1;

	if (argc == 2 && !strcmp(argv[1], "-h"))
		usage_with_options(builtin_branch_usage, options);

	git_config(git_branch_config, NULL);

	track = git_branch_track;

	head = resolve_refdup("HEAD", 0, head_sha1, NULL);
	if (!head)
		die(_("Failed to resolve HEAD as a valid ref."));
	if (!strcmp(head, "HEAD"))
		filter.detached = 1;
	else if (!skip_prefix(head, "refs/heads/", &head))
		die(_("HEAD not found below refs/heads!"));
