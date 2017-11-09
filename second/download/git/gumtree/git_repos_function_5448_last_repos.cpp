static int merge_tree(struct tree *tree)
{
	struct lock_file *lock_file;
	struct unpack_trees_options opts;
	struct tree_desc t[1];

	if (parse_tree(tree))
		return -1;

	lock_file = xcalloc(1, sizeof(struct lock_file));
	hold_locked_index(lock_file, LOCK_DIE_ON_ERROR);

	memset(&opts, 0, sizeof(opts));
	opts.head_idx = 1;
	opts.src_index = &the_index;
	opts.dst_index = &the_index;
	opts.merge = 1;
	opts.fn = oneway_merge;
	init_tree_desc(&t[0], tree->buffer, tree->size);

	if (unpack_trees(1, t, &opts)) {
		rollback_lock_file(lock_file);
		return -1;
	}

	if (write_locked_index(&the_index, lock_file, COMMIT_LOCK))
		die(_("unable to write new index file"));

	return 0;
}