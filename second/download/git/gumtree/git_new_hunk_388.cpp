		usage_with_options(git_notes_add_usage, options);
	}

	object_ref = argc > 1 ? argv[1] : "HEAD";

	if (get_sha1(object_ref, object))
		die(_("failed to resolve '%s' as a valid ref."), object_ref);

	t = init_notes_check("add", NOTES_INIT_WRITABLE);
	note = get_note(t, object);

	if (note) {
		if (!force) {
