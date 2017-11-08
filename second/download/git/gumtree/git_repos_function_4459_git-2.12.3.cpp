int remove_note(struct notes_tree *t, const unsigned char *object_sha1)
{
	struct leaf_node l;

	if (!t)
		t = &default_notes_tree;
	assert(t->initialized);
	hashcpy(l.key_sha1, object_sha1);
	hashclr(l.val_sha1);
	note_tree_remove(t, t->root, 0, &l);
	if (is_null_sha1(l.val_sha1)) /* no note was removed */
		return 1;
	t->dirty = 1;
	return 0;
}