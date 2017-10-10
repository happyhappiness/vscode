	save_commit_buffer = 0;

	if (longformat && abbrev == 0)
		die(_("--long is incompatible with --abbrev=0"));

	if (contains) {
		struct string_list_item *item;
		struct argv_array args;

		argv_array_init(&args);
		argv_array_pushl(&args, "name-rev",
				 "--peel-tag", "--name-only", "--no-undefined",
				 NULL);
		if (always)
			argv_array_push(&args, "--always");
		if (!all) {
			argv_array_push(&args, "--tags");
			for_each_string_list_item(item, &patterns)
				argv_array_pushf(&args, "--refs=refs/tags/%s", item->string);
			for_each_string_list_item(item, &exclude_patterns)
				argv_array_pushf(&args, "--exclude=refs/tags/%s", item->string);
		}
		if (argc)
			argv_array_pushv(&args, argv);
		else
			argv_array_push(&args, "HEAD");
		return cmd_name_rev(args.argc, args.argv, prefix);
