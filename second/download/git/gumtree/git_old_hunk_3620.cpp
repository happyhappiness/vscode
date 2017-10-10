{
	int ret;
	struct lock_file *lock_file = xcalloc(1, sizeof(struct lock_file));

	hold_locked_index(lock_file, 1);
	if (read_cache_preload(NULL) < 0)
		return error(_("corrupt index file"));

	resolve_undo_clear();
	if (opts->force) {
		ret = reset_tree(new->commit->tree, opts, 1, writeout_error);
		if (ret)
			return ret;
