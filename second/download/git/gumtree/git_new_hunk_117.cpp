
	git_config(git_default_config, NULL);

	argc = parse_options(argc, argv, unused_prefix, read_tree_options,
			     read_tree_usage, 0);

	hold_locked_index(&lock_file, 1);

	prefix_set = opts.prefix ? 1 : 0;
	if (1 < opts.merge + opts.reset + prefix_set)
		die("Which one? -m, --reset, or --prefix?");

	/*
	 * NEEDSWORK
	 *
	 * The old index should be read anyway even if we're going to
	 * destroy all index entries because we still need to preserve
	 * certain information such as index version or split-index
	 * mode.
	 */

	if (opts.reset || opts.merge || opts.prefix) {
		if (read_cache_unmerged() && (opts.prefix || opts.merge))
			die("You need to resolve your current index first");
		stage = opts.merge = 1;
	}
	resolve_undo_clear();
