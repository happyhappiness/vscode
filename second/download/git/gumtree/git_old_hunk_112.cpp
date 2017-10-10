
	argc = parse_options(argc, argv, prefix, builtin_mv_options,
			     builtin_mv_usage, 0);
	if (--argc < 1)
		usage_with_options(builtin_mv_usage, builtin_mv_options);

	newfd = hold_locked_index(&lock_file, 1);
	if (read_cache() < 0)
		die(_("index file corrupt"));

	source = internal_copy_pathspec(prefix, argv, argc, 0);
	modes = xcalloc(argc, sizeof(enum update_mode));
	/*
