static int fast_forward_to(struct tree *head, struct tree *remote, int reset)
{
	struct lock_file *lock_file;
	struct unpack_trees_options opts;
	struct tree_desc t[2];

	if (parse_tree(head) || parse_tree(remote))
		return -1;

	lock_file = xcalloc(1, sizeof(struct lock_file));
	hold_locked_index(lock_file, LOCK_DIE_ON_ERROR);

	refresh_cache(REFRESH_QUIET);

	memset(&opts, 0, sizeof(opts));
	opts.head_idx = 1;
	opts.src_index = &the_index;
	opts.dst_index = &the_index;
	opts.update = 1;
	opts.merge = 1;
	opts.reset = reset;
	opts.fn = twoway_merge;
	init_tree_desc(&t[0], head->buffer, head->size);
	init_tree_desc(&t[1], remote->buffer, remote->size);

	if (unpack_trees(2, t, &opts)) {
		rollback_lock_file(lock_file);
		return -1;
	}

	if (write_locked_index(&the_index, lock_file, COMMIT_LOCK))
		die(_("unable to write new index file"));

	return 0;
}