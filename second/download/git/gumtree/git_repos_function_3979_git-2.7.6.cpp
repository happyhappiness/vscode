void free_notes(struct notes_tree *t)
{
	if (!t)
		t = &default_notes_tree;
	if (t->root)
		note_tree_free(t->root);
	free(t->root);
	while (t->first_non_note) {
		t->prev_non_note = t->first_non_note->next;
		free(t->first_non_note->path);
		free(t->first_non_note);
		t->first_non_note = t->prev_non_note;
	}
	free(t->ref);
	memset(t, 0, sizeof(struct notes_tree));
}