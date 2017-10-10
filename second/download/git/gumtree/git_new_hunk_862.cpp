			     N_("field name to sort on"), &parse_opt_ref_sorting),
		{
			OPTION_CALLBACK, 0, "points-at", &filter.points_at, N_("object"),
			N_("print only branches of the object"), 0, parse_opt_object_name
		},
		OPT_BOOL('i', "ignore-case", &icase, N_("sorting and filtering are case insensitive")),
		OPT_STRING(  0 , "format", &format, N_("format"), N_("format to use for the output")),
		OPT_END(),
	};

	setup_ref_filter_porcelain_msg();

	memset(&filter, 0, sizeof(filter));
	filter.kind = FILTER_REFS_BRANCHES;
	filter.abbrev = -1;

	if (argc == 2 && !strcmp(argv[1], "-h"))
		usage_with_options(builtin_branch_usage, options);

	git_config(git_branch_config, NULL);

	track = git_branch_track;

	head = resolve_refdup("HEAD", 0, head_oid.hash, NULL);
	if (!head)
		die(_("Failed to resolve HEAD as a valid ref."));
	if (!strcmp(head, "HEAD"))
		filter.detached = 1;
	else if (!skip_prefix(head, "refs/heads/", &head))
		die(_("HEAD not found below refs/heads!"));
