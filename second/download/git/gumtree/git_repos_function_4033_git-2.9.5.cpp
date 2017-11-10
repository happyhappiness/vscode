static int note_tree_insert(struct notes_tree *t, struct int_node *tree,
		unsigned char n, struct leaf_node *entry, unsigned char type,
		combine_notes_fn combine_notes)
{
	struct int_node *new_node;
	struct leaf_node *l;
	void **p = note_tree_search(t, &tree, &n, entry->key_sha1);
	int ret = 0;

	assert(GET_PTR_TYPE(entry) == 0); /* no type bits set */
	l = (struct leaf_node *) CLR_PTR_TYPE(*p);
	switch (GET_PTR_TYPE(*p)) {
	case PTR_TYPE_NULL:
		assert(!*p);
		if (is_null_sha1(entry->val_sha1))
			free(entry);
		else
			*p = SET_PTR_TYPE(entry, type);
		return 0;
	case PTR_TYPE_NOTE:
		switch (type) {
		case PTR_TYPE_NOTE:
			if (!hashcmp(l->key_sha1, entry->key_sha1)) {
				/* skip concatenation if l == entry */
				if (!hashcmp(l->val_sha1, entry->val_sha1))
					return 0;

				ret = combine_notes(l->val_sha1,
						    entry->val_sha1);
				if (!ret && is_null_sha1(l->val_sha1))
					note_tree_remove(t, tree, n, entry);
				free(entry);
				return ret;
			}
			break;
		case PTR_TYPE_SUBTREE:
			if (!SUBTREE_SHA1_PREFIXCMP(l->key_sha1,
						    entry->key_sha1)) {
				/* unpack 'entry' */
				load_subtree(t, entry, tree, n);
				free(entry);
				return 0;
			}
			break;
		}
		break;
	case PTR_TYPE_SUBTREE:
		if (!SUBTREE_SHA1_PREFIXCMP(entry->key_sha1, l->key_sha1)) {
			/* unpack 'l' and restart insert */
			*p = NULL;
			load_subtree(t, l, tree, n);
			free(l);
			return note_tree_insert(t, tree, n, entry, type,
						combine_notes);
		}
		break;
	}

	/* non-matching leaf_node */
	assert(GET_PTR_TYPE(*p) == PTR_TYPE_NOTE ||
	       GET_PTR_TYPE(*p) == PTR_TYPE_SUBTREE);
	if (is_null_sha1(entry->val_sha1)) { /* skip insertion of empty note */
		free(entry);
		return 0;
	}
	new_node = (struct int_node *) xcalloc(1, sizeof(struct int_node));
	ret = note_tree_insert(t, new_node, n + 1, l, GET_PTR_TYPE(*p),
			       combine_notes);
	if (ret)
		return ret;
	*p = SET_PTR_TYPE(new_node, PTR_TYPE_INTERNAL);
	return note_tree_insert(t, new_node, n + 1, entry, type, combine_notes);
}