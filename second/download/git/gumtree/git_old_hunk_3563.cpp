		OPT_END()
	};

	argc = parse_options(argc, argv, NULL, opts, archive_usage, 0);

	if (remote)
		die("Unexpected option --remote");
	if (exec)
		die("Option --exec can only be used together with --remote");
	if (output)
		die("Unexpected option --output");

	if (!base)
		base = "";

	if (list) {
		for (i = 0; i < nr_archivers; i++)
