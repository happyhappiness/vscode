
	object_ref = argc ? argv[0] : "HEAD";

	if (get_sha1(object_ref, object))
		die(_("Failed to resolve '%s' as a valid ref."), object_ref);

	t = init_notes_check("show");
	note = get_note(t, object);

	if (!note)
		retval = error(_("No note found for object %s."),
			       sha1_to_hex(object));
	else {
