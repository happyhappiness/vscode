			argv_array_pushv(&args, argv);
		else
			argv_array_push(&args, "HEAD");
		return cmd_name_rev(args.argc, args.argv, prefix);
	}

	hashmap_init(&names, (hashmap_cmp_fn) commit_name_cmp, 0);
	for_each_rawref(get_name, NULL);
	if (!names.size && !always)
		die(_("No names found, cannot describe anything."));

	if (argc == 0) {
		if (broken) {
