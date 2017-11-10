int for_each_note(struct notes_tree *t, int flags, each_note_fn fn,
		void *cb_data)
{
	if (!t)
		t = &default_notes_tree;
	assert(t->initialized);
	return for_each_note_helper(t, t->root, 0, 0, flags, fn, cb_data);
}