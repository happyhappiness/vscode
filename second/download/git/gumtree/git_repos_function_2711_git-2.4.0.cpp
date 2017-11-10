int write_cache_as_tree(unsigned char *sha1, int flags, const char *prefix)
{
	int entries, was_valid, newfd;
	struct lock_file *lock_file;

	/*
	 * We can't free this memory, it becomes part of a linked list
	 * parsed atexit()
	 */
	lock_file = xcalloc(1, sizeof(struct lock_file));

	newfd = hold_locked_index(lock_file, 1);

	entries = read_cache();
	if (entries < 0)
		return WRITE_TREE_UNREADABLE_INDEX;
	if (flags & WRITE_TREE_IGNORE_CACHE_TREE)
		cache_tree_free(&(active_cache_tree));

	if (!active_cache_tree)
		active_cache_tree = cache_tree();

	was_valid = cache_tree_fully_valid(active_cache_tree);
	if (!was_valid) {
		if (cache_tree_update(&the_index, flags) < 0)
			return WRITE_TREE_UNMERGED_INDEX;
		if (0 <= newfd) {
			if (!write_locked_index(&the_index, lock_file, COMMIT_LOCK))
				newfd = -1;
		}
		/* Not being able to write is fine -- we are only interested
		 * in updating the cache-tree part, and if the next caller
		 * ends up using the old index with unupdated cache-tree part
		 * it misses the work we did here, but that is just a
		 * performance penalty and not a big deal.
		 */
	}

	if (prefix) {
		struct cache_tree *subtree =
			cache_tree_find(active_cache_tree, prefix);
		if (!subtree)
			return WRITE_TREE_PREFIX_ERROR;
		hashcpy(sha1, subtree->sha1);
	}
	else
		hashcpy(sha1, active_cache_tree->sha1);

	if (0 <= newfd)
		rollback_lock_file(lock_file);

	return 0;
}