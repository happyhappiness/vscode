tatic int show(int argc, const char **argv, const char *prefix)
{
	const char *object_ref;
	struct notes_tree *t;
	unsigned char object[20];
	const unsigned char *note;
	int retval;
	struct option options[] = {
		OPT_END()
	};

	argc = parse_options(argc, argv, prefix, options, git_notes_show_usage,
			     0);

	if (1 < argc) {
		error(_("too many parameters"));
		usage_with_options(git_notes_show_usage, options);
	}

	object_ref = argc ? argv[0] : "HEAD";

	if (get_sha1(object_ref, object))
		die(_("failed to resolve '%s' as a valid ref."), object_ref);

	t = init_notes_check("show", 0);
	note = get_note(t, object);

	if (!note)
		retval = error(_("no note found for object %s."),
			       sha1_to_hex(object));
	else {
		const char *show_args[3] = {"show", sha1_to_hex(note), NULL};
		retval = execv_git_cmd(show_args);
	}
	free_notes(t);
	return retval;
}