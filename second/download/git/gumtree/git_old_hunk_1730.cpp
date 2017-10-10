	if (!bmo)
		return;
	argc = split_cmdline(bmo, &argv);
	if (argc < 0)
		die(_("Bad branch.%s.mergeoptions string: %s"), branch,
		    split_cmdline_strerror(argc));
	argv = xrealloc(argv, sizeof(*argv) * (argc + 2));
	memmove(argv + 1, argv, sizeof(*argv) * (argc + 1));
	argc++;
	argv[0] = "branch.*.mergeoptions";
	parse_options(argc, argv, NULL, builtin_merge_options,
		      builtin_merge_usage, 0);
	free(argv);
