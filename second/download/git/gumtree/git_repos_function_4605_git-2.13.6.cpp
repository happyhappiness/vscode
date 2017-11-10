static int write_each_note_helper(struct tree_write_stack *tws,
		const char *path, unsigned int mode,
		const unsigned char *sha1)
{
	size_t path_len = strlen(path);
	unsigned int n = 0;
	int ret;

	/* Determine common part of tree write stack */
	while (tws && 3 * n < path_len &&
	       matches_tree_write_stack(tws, path + 3 * n)) {
		n++;
		tws = tws->next;
	}

	/* tws point to last matching tree_write_stack entry */
	ret = tree_write_stack_finish_subtree(tws);
	if (ret)
		return ret;

	/* Start subtrees needed to satisfy path */
	while (3 * n + 2 < path_len && path[3 * n + 2] == '/') {
		tree_write_stack_init_subtree(tws, path + 3 * n);
		n++;
		tws = tws->next;
	}

	/* There should be no more directory components in the given path */
	assert(memchr(path + 3 * n, '/', path_len - (3 * n)) == NULL);

	/* Finally add given entry to the current tree object */
	write_tree_entry(&tws->buf, mode, path + 3 * n, path_len - (3 * n),
			 sha1);

	return 0;
}