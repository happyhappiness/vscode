int cmd_read_tree(int argc, const char **argv, const char *unused_prefix)
{
	int i, newfd, stage = 0;
	unsigned char sha1[20];
	struct tree_desc t[MAX_UNPACK_TREES];
	struct unpack_trees_options opts;
	int prefix_set = 0;
	const struct option read_tree_options[] = {
		{ OPTION_CALLBACK, 0, "index-output", NULL, N_("file"),
		  N_("write resulting index to <file>"),
		  PARSE_OPT_NONEG, index_output_cb },
		OPT_SET_INT(0, "empty", &read_empty,
			    N_("only empty the index"), 1),
		OPT__VERBOSE(&opts.verbose_update, N_("be verbose")),
		OPT_GROUP(N_("Merging")),
		OPT_SET_INT('m', NULL, &opts.merge,
			    N_("perform a merge in addition to a read"), 1),
		OPT_SET_INT(0, "trivial", &opts.trivial_merges_only,
			    N_("3-way merge if no file level merging required"), 1),
		OPT_SET_INT(0, "aggressive", &opts.aggressive,
			    N_("3-way merge in presence of adds and removes"), 1),
		OPT_SET_INT(0, "reset", &opts.reset,
			    N_("same as -m, but discard unmerged entries"), 1),
		{ OPTION_STRING, 0, "prefix", &opts.prefix, N_("<subdirectory>/"),
		  N_("read the tree into the index under <subdirectory>/"),
		  PARSE_OPT_NONEG | PARSE_OPT_LITERAL_ARGHELP },
		OPT_SET_INT('u', NULL, &opts.update,
			    N_("update working tree with merge result"), 1),
		{ OPTION_CALLBACK, 0, "exclude-per-directory", &opts,
		  N_("gitignore"),
		  N_("allow explicitly ignored files to be overwritten"),
		  PARSE_OPT_NONEG, exclude_per_directory_cb },
		OPT_SET_INT('i', NULL, &opts.index_only,
			    N_("don't check the working tree after merging"), 1),
		OPT__DRY_RUN(&opts.dry_run, N_("don't update the index or the work tree")),
		OPT_SET_INT(0, "no-sparse-checkout", &opts.skip_sparse_checkout,
			    N_("skip applying sparse checkout filter"), 1),
		OPT_SET_INT(0, "debug-unpack", &opts.debug_unpack,
			    N_("debug unpack-trees"), 1),
		OPT_END()
	};

	memset(&opts, 0, sizeof(opts));
	opts.head_idx = -1;
	opts.src_index = &the_index;
	opts.dst_index = &the_index;

	git_config(git_default_config, NULL);

	argc = parse_options(argc, argv, unused_prefix, read_tree_options,
			     read_tree_usage, 0);

	newfd = hold_locked_index(&lock_file, 1);

	prefix_set = opts.prefix ? 1 : 0;
	if (1 < opts.merge + opts.reset + prefix_set)
		die("Which one? -m, --reset, or --prefix?");

	if (opts.reset || opts.merge || opts.prefix) {
		if (read_cache_unmerged() && (opts.prefix || opts.merge))
			die("You need to resolve your current index first");
		stage = opts.merge = 1;
	}
	resolve_undo_clear();

	for (i = 0; i < argc; i++) {
		const char *arg = argv[i];

		if (get_sha1(arg, sha1))
			die("Not a valid object name %s", arg);
		if (list_tree(sha1) < 0)
			die("failed to unpack tree object %s", arg);
		stage++;
	}
	if (nr_trees == 0 && !read_empty)
		warning("read-tree: emptying the index with no arguments is deprecated; use --empty");
	else if (nr_trees > 0 && read_empty)
		die("passing trees as arguments contradicts --empty");

	if (1 < opts.index_only + opts.update)
		die("-u and -i at the same time makes no sense");
	if ((opts.update || opts.index_only) && !opts.merge)
		die("%s is meaningless without -m, --reset, or --prefix",
		    opts.update ? "-u" : "-i");
	if ((opts.dir && !opts.update))
		die("--exclude-per-directory is meaningless unless -u");
	if (opts.merge && !opts.index_only)
		setup_work_tree();

	if (opts.merge) {
		if (stage < 2)
			die("just how do you expect me to merge %d trees?", stage-1);
		switch (stage - 1) {
		case 1:
			opts.fn = opts.prefix ? bind_merge : oneway_merge;
			break;
		case 2:
			opts.fn = twoway_merge;
			opts.initial_checkout = is_cache_unborn();
			break;
		case 3:
		default:
			opts.fn = threeway_merge;
			break;
		}

		if (stage - 1 >= 3)
			opts.head_idx = stage - 2;
		else
			opts.head_idx = 1;
	}

	if (opts.debug_unpack)
		opts.fn = debug_merge;

	cache_tree_free(&active_cache_tree);
	for (i = 0; i < nr_trees; i++) {
		struct tree *tree = trees[i];
		parse_tree(tree);
		init_tree_desc(t+i, tree->buffer, tree->size);
	}
	if (unpack_trees(nr_trees, t, &opts))
		return 128;

	if (opts.debug_unpack || opts.dry_run)
		return 0; /* do not write the index out */

	/*
	 * When reading only one tree (either the most basic form,
	 * "-m ent" or "--reset ent" form), we can obtain a fully
	 * valid cache-tree because the index must match exactly
	 * what came from the tree.
	 */
	if (nr_trees == 1 && !opts.prefix)
		prime_cache_tree(&active_cache_tree, trees[0]);

	if (write_cache(newfd, active_cache, active_nr) ||
	    commit_locked_index(&lock_file))
		die("unable to write new index file");
	return 0;
}