	if (opts->patch_mode)
		return run_add_interactive(revision, "--patch=checkout",
					   &opts->pathspec);

	lock_file = xcalloc(1, sizeof(struct lock_file));

	newfd = hold_locked_index(lock_file, 1);
	if (read_cache_preload(&opts->pathspec) < 0)
		return error(_("corrupt index file"));

	if (opts->source_tree)
		read_tree_some(opts->source_tree, &opts->pathspec);

