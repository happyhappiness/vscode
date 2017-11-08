static int prune_notes_helper(const unsigned char *object_sha1,
		const unsigned char *note_sha1, char *note_path,
		void *cb_data)
{
	struct note_delete_list **l = (struct note_delete_list **) cb_data;
	struct note_delete_list *n;

	if (has_sha1_file(object_sha1))
		return 0; /* nothing to do for this note */

	/* failed to find object => prune this note */
	n = (struct note_delete_list *) xmalloc(sizeof(*n));
	n->next = *l;
	n->sha1 = object_sha1;
	*l = n;
	return 0;
}