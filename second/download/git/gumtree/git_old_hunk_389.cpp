	if (2 < argc) {
		error(_("too many parameters"));
		usage_with_options(git_notes_copy_usage, options);
	}

	if (get_sha1(argv[0], from_obj))
		die(_("Failed to resolve '%s' as a valid ref."), argv[0]);

	object_ref = 1 < argc ? argv[1] : "HEAD";

	if (get_sha1(object_ref, object))
		die(_("Failed to resolve '%s' as a valid ref."), object_ref);

	t = init_notes_check("copy", NOTES_INIT_WRITABLE);
	note = get_note(t, object);

	if (note) {
		if (!force) {
