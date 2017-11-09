int copy_note(struct notes_tree *t,
	      const struct object_id *from_obj, const struct object_id *to_obj,
	      int force, combine_notes_fn combine_notes)
{
	const struct object_id *note = get_note(t, from_obj);
	const struct object_id *existing_note = get_note(t, to_obj);

	if (!force && existing_note)
		return 1;

	if (note)
		return add_note(t, to_obj, note, combine_notes);
	else if (existing_note)
		return add_note(t, to_obj, &null_oid, combine_notes);

	return 0;
}