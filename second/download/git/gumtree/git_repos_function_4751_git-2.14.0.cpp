int write_notes_tree(struct notes_tree *t, unsigned char *result)
{
	struct tree_write_stack root;
	struct write_each_note_data cb_data;
	int ret;

	if (!t)
		t = &default_notes_tree;
	assert(t->initialized);

	/* Prepare for traversal of current notes tree */
	root.next = NULL; /* last forward entry in list is grounded */
	strbuf_init(&root.buf, 256 * (32 + GIT_SHA1_HEXSZ)); /* assume 256 entries */
	root.path[0] = root.path[1] = '\0';
	cb_data.root = &root;
	cb_data.next_non_note = t->first_non_note;

	/* Write tree objects representing current notes tree */
	ret = for_each_note(t, FOR_EACH_NOTE_DONT_UNPACK_SUBTREES |
				FOR_EACH_NOTE_YIELD_SUBTREES,
			write_each_note, &cb_data) ||
		write_each_non_note_until(NULL, &cb_data) ||
		tree_write_stack_finish_subtree(&root) ||
		write_sha1_file(root.buf.buf, root.buf.len, tree_type, result);
	strbuf_release(&root.buf);
	return ret;
}