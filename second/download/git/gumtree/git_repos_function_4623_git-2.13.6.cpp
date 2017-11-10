int add_note(struct notes_tree *t, const unsigned char *object_sha1,
		const unsigned char *note_sha1, combine_notes_fn combine_notes)
{
	struct leaf_node *l;

	if (!t)
		t = &default_notes_tree;
	assert(t->initialized);
	t->dirty = 1;
	if (!combine_notes)
		combine_notes = t->combine_notes;
	l = (struct leaf_node *) xmalloc(sizeof(struct leaf_node));
	hashcpy(l->key_sha1, object_sha1);
	hashcpy(l->val_sha1, note_sha1);
	return note_tree_insert(t, t->root, 0, l, PTR_TYPE_NOTE, combine_notes);
}