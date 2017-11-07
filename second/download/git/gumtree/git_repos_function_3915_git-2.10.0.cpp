int checkout_fast_forward(const unsigned char *head,
			  const unsigned char *remote,
			  int overwrite_ignore)
{
	struct tree *trees[MAX_UNPACK_TREES];
	struct unpack_trees_options opts;
	struct tree_desc t[MAX_UNPACK_TREES];
	int i, nr_trees = 0;
	struct dir_struct dir;
	struct lock_file *lock_file = xcalloc(1, sizeof(struct lock_file));

	refresh_cache(REFRESH_QUIET);

	hold_locked_index(lock_file, 1);

	memset(&trees, 0, sizeof(trees));
	memset(&opts, 0, sizeof(opts));
	memset(&t, 0, sizeof(t));
	if (overwrite_ignore) {
		memset(&dir, 0, sizeof(dir));
		dir.flags |= DIR_SHOW_IGNORED;
		setup_standard_excludes(&dir);
		opts.dir = &dir;
	}

	opts.head_idx = 1;
	opts.src_index = &the_index;
	opts.dst_index = &the_index;
	opts.update = 1;
	opts.verbose_update = 1;
	opts.merge = 1;
	opts.fn = twoway_merge;
	setup_unpack_trees_porcelain(&opts, "merge");

	trees[nr_trees] = parse_tree_indirect(head);
	if (!trees[nr_trees++])
		return -1;
	trees[nr_trees] = parse_tree_indirect(remote);
	if (!trees[nr_trees++])
		return -1;
	for (i = 0; i < nr_trees; i++) {
		parse_tree(trees[i]);
		init_tree_desc(t+i, trees[i]->buffer, trees[i]->size);
	}
	if (unpack_trees(nr_trees, t, &opts))
		return -1;
	if (write_locked_index(&the_index, lock_file, COMMIT_LOCK))
		die(_("unable to write new index file"));
	return 0;
}