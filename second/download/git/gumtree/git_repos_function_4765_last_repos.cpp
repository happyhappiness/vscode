int add_note(struct notes_tree *t, const struct object_id *object_oid,
		const struct object_id *note_oid, combine_notes_fn combine_notes)
{
	struct leaf_node *l;

	if (!t)
		t = &default_notes_tree;
	assert(t->initialized);
	t->dirty = 1;
	if (!combine_notes)
		combine_notes = t->combine_notes;
	l = (struct leaf_node *) xmalloc(sizeof(struct leaf_node));
	oidcpy(&l->key_oid, object_oid);
	oidcpy(&l->val_oid, note_oid);
	return note_tree_insert(t, t->root, 0, l, PTR_TYPE_NOTE, combine_notes);
}