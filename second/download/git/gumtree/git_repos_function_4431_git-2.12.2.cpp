static int for_each_note_helper(struct notes_tree *t, struct int_node *tree,
		unsigned char n, unsigned char fanout, int flags,
		each_note_fn fn, void *cb_data)
{
	unsigned int i;
	void *p;
	int ret = 0;
	struct leaf_node *l;
	static char path[FANOUT_PATH_MAX];

	fanout = determine_fanout(tree, n, fanout);
	for (i = 0; i < 16; i++) {
redo:
		p = tree->a[i];
		switch (GET_PTR_TYPE(p)) {
		case PTR_TYPE_INTERNAL:
			/* recurse into int_node */
			ret = for_each_note_helper(t, CLR_PTR_TYPE(p), n + 1,
				fanout, flags, fn, cb_data);
			break;
		case PTR_TYPE_SUBTREE:
			l = (struct leaf_node *) CLR_PTR_TYPE(p);
			/*
			 * Subtree entries in the note tree represent parts of
			 * the note tree that have not yet been explored. There
			 * is a direct relationship between subtree entries at
			 * level 'n' in the tree, and the 'fanout' variable:
			 * Subtree entries at level 'n <= 2 * fanout' should be
			 * preserved, since they correspond exactly to a fanout
			 * directory in the on-disk structure. However, subtree
			 * entries at level 'n > 2 * fanout' should NOT be
			 * preserved, but rather consolidated into the above
			 * notes tree level. We achieve this by unconditionally
			 * unpacking subtree entries that exist below the
			 * threshold level at 'n = 2 * fanout'.
			 */
			if (n <= 2 * fanout &&
			    flags & FOR_EACH_NOTE_YIELD_SUBTREES) {
				/* invoke callback with subtree */
				unsigned int path_len =
					l->key_sha1[19] * 2 + fanout;
				assert(path_len < FANOUT_PATH_MAX - 1);
				construct_path_with_fanout(l->key_sha1, fanout,
							   path);
				/* Create trailing slash, if needed */
				if (path[path_len - 1] != '/')
					path[path_len++] = '/';
				path[path_len] = '\0';
				ret = fn(l->key_sha1, l->val_sha1, path,
					 cb_data);
			}
			if (n > fanout * 2 ||
			    !(flags & FOR_EACH_NOTE_DONT_UNPACK_SUBTREES)) {
				/* unpack subtree and resume traversal */
				tree->a[i] = NULL;
				load_subtree(t, l, tree, n);
				free(l);
				goto redo;
			}
			break;
		case PTR_TYPE_NOTE:
			l = (struct leaf_node *) CLR_PTR_TYPE(p);
			construct_path_with_fanout(l->key_sha1, fanout, path);
			ret = fn(l->key_sha1, l->val_sha1, path, cb_data);
			break;
		}
		if (ret)
			return ret;
	}
	return 0;
}