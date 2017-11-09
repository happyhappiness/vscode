static int list(int argc, const char **argv, const char *prefix)
{
	struct notes_tree *t;
	struct object_id object;
	const struct object_id *note;
	int retval = -1;
	struct option options[] = {
		OPT_END()
	};

	if (argc)
		argc = parse_options(argc, argv, prefix, options,
				     git_notes_list_usage, 0);

	if (1 < argc) {
		error(_("too many parameters"));
		usage_with_options(git_notes_list_usage, options);
	}

	t = init_notes_check("list", 0);
	if (argc) {
		if (get_oid(argv[0], &object))
			die(_("failed to resolve '%s' as a valid ref."), argv[0]);
		note = get_note(t, &object);
		if (note) {
			puts(oid_to_hex(note));
			retval = 0;
		} else
			retval = error(_("no note found for object %s."),
				       oid_to_hex(&object));
	} else
		retval = for_each_note(t, 0, list_each_note, NULL);

	free_notes(t);
	return retval;
}