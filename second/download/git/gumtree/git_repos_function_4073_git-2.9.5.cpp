int copy_note(struct notes_tree *t,
	      const unsigned char *from_obj, const unsigned char *to_obj,
	      int force, combine_notes_fn combine_notes)
{
	const unsigned char *note = get_note(t, from_obj);
	const unsigned char *existing_note = get_note(t, to_obj);

	if (!force && existing_note)
		return 1;

	if (note)
		return add_note(t, to_obj, note, combine_notes);
	else if (existing_note)
		return add_note(t, to_obj, null_sha1, combine_notes);

	return 0;
}