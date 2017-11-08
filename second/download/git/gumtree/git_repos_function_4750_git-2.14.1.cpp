const struct object_id *get_note(struct notes_tree *t,
		const struct object_id *oid)
{
	struct leaf_node *found;

	if (!t)
		t = &default_notes_tree;
	assert(t->initialized);
	found = note_tree_find(t, t->root, 0, oid->hash);
	return found ? &found->val_oid : NULL;
}