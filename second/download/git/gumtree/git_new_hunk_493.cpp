	t->update_ref = (flags & NOTES_INIT_WRITABLE) ? t->ref : NULL;
	t->combine_notes = combine_notes;
	t->initialized = 1;
	t->dirty = 0;

	if (flags & NOTES_INIT_EMPTY || !notes_ref ||
	    get_sha1_treeish(notes_ref, object_oid.hash))
		return;
	if (flags & NOTES_INIT_WRITABLE && read_ref(notes_ref, object_oid.hash))
		die("Cannot use notes ref %s", notes_ref);
	if (get_tree_entry(object_oid.hash, "", oid.hash, &mode))
		die("Failed to read notes tree referenced by %s (%s)",
		    notes_ref, oid_to_hex(&object_oid));

	hashclr(root_tree.key_sha1);
	hashcpy(root_tree.val_sha1, oid.hash);
	load_subtree(t, &root_tree, t->root, 0);
}

struct notes_tree **load_notes_trees(struct string_list *refs, int flags)
{
	struct string_list_item *item;
