int write_index_as_tree(unsigned char *sha1, struct index_state *index_state, const char *index_path, int flags, const char *prefix)
{
	int entries, was_valid, newfd;
	struct lock_file *lock_file;

	/*
	 * We can't free this memory, it becomes part of a linked list
	 * parsed atexit()
	 */
	lock_file = xcalloc(1, sizeof(struct lock_file));

	newfd = hold_lock_file_for_update(lock_file, index_path, LOCK_DIE_ON_ERROR);

	entries = read_index_from(index_state, index_path);
	if (entries < 0)
		return WRITE_TREE_UNREADABLE_INDEX;
	if (flags & WRITE_TREE_IGNORE_CACHE_TREE)
		cache_tree_free(&index_state->cache_tree);

	if (!index_state->cache_tree)
		index_state->cache_tree = cache_tree();

	was_valid = cache_tree_fully_valid(index_state->cache_tree);
	if (!was_valid) {
		if (cache_tree_update(index_state, flags) < 0)
			return WRITE_TREE_UNMERGED_INDEX;
		if (0 <= newfd) {
			if (!write_locked_index(index_state, lock_file, COMMIT_LOCK))
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
		struct cache_tree *subtree;
		subtree = cache_tree_find(index_state->cache_tree, prefix);
		if (!subtree)
			return WRITE_TREE_PREFIX_ERROR;
		hashcpy(sha1, subtree->sha1);
	}
	else
		hashcpy(sha1, index_state->cache_tree->sha1);

	if (0 <= newfd)
		rollback_lock_file(lock_file);

	return 0;
}