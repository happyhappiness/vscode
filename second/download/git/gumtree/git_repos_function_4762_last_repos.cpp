void init_notes(struct notes_tree *t, const char *notes_ref,
		combine_notes_fn combine_notes, int flags)
{
	struct object_id oid, object_oid;
	unsigned mode;
	struct leaf_node root_tree;

	if (!t)
		t = &default_notes_tree;
	assert(!t->initialized);

	if (!notes_ref)
		notes_ref = default_notes_ref();

	if (!combine_notes)
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
	    get_sha1_treeish(notes_ref, object_oid.hash))
		return;
	if (flags & NOTES_INIT_WRITABLE && read_ref(notes_ref, object_oid.hash))
		die("Cannot use notes ref %s", notes_ref);
	if (get_tree_entry(object_oid.hash, "", oid.hash, &mode))
		die("Failed to read notes tree referenced by %s (%s)",
		    notes_ref, oid_to_hex(&object_oid));

	oidclr(&root_tree.key_oid);
	oidcpy(&root_tree.val_oid, &oid);
	load_subtree(t, &root_tree, t->root, 0);
}