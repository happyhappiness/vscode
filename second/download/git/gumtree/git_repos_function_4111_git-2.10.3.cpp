const unsigned char *get_note(struct notes_tree *t,
		const unsigned char *object_sha1)
{
	struct leaf_node *found;

	if (!t)
		t = &default_notes_tree;
	assert(t->initialized);
	found = note_tree_find(t, t->root, 0, object_sha1);
	return found ? found->val_sha1 : NULL;
}