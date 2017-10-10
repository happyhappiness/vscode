		combine_notes = combine_notes_concatenate;

	t->root = (struct int_node *) xcalloc(1, sizeof(struct int_node));
	t->first_non_note = NULL;
	t->prev_non_note = NULL;
	t->ref = xstrdup_or_null(notes_ref);
	t->update_ref = (flags & NOTES_INIT_WRITABLE) ? t->ref : NULL;
	t->combine_notes = combine_notes;
	t->initialized = 1;
	t->dirty = 0;

	if (flags & NOTES_INIT_EMPTY || !notes_ref ||
	    get_sha1_treeish(notes_ref, object_sha1))
		return;
	if (flags & NOTES_INIT_WRITABLE && read_ref(notes_ref, object_sha1))
		die("Cannot use notes ref %s", notes_ref);
	if (get_tree_entry(object_sha1, "", sha1, &mode))
		die("Failed to read notes tree referenced by %s (%s)",
		    notes_ref, sha1_to_hex(object_sha1));

	hashclr(root_tree.key_sha1);
	hashcpy(root_tree.val_sha1, sha1);
	load_subtree(t, &root_tree, t->root, 0);
}

struct notes_tree **load_notes_trees(struct string_list *refs, int flags)
{
	struct string_list_item *item;
	int counter = 0;
	struct notes_tree **trees;
	ALLOC_ARRAY(trees, refs->nr + 1);
	for_each_string_list_item(item, refs) {
		struct notes_tree *t = xcalloc(1, sizeof(struct notes_tree));
		init_notes(t, item->string, combine_notes_ignore, flags);
		trees[counter++] = t;
	}
	trees[counter] = NULL;
	return trees;
}

