	save_commit_buffer = 0;

	if (longformat && abbrev == 0)
		die(_("--long is incompatible with --abbrev=0"));

	if (contains) {
		struct argv_array args;

		argv_array_init(&args);
		argv_array_pushl(&args, "name-rev",
				 "--peel-tag", "--name-only", "--no-undefined",
				 NULL);
		if (always)
			argv_array_push(&args, "--always");
		if (!all) {
			argv_array_push(&args, "--tags");
			if (pattern)
				argv_array_pushf(&args, "--refs=refs/tags/%s", pattern);
		}
		if (argc)
			argv_array_pushv(&args, argv);
		else
			argv_array_push(&args, "HEAD");
		return cmd_name_rev(args.argc, args.argv, prefix);
