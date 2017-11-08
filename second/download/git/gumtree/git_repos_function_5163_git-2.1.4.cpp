static int append_edit(int argc, const char **argv, const char *prefix)
{
	const char *object_ref;
	struct notes_tree *t;
	unsigned char object[20], new_note[20];
	const unsigned char *note;
	char logmsg[100];
	const char * const *usage;
	struct msg_arg msg = { 0, 0, STRBUF_INIT };
	struct option options[] = {
		{ OPTION_CALLBACK, 'm', "message", &msg, N_("message"),
			N_("note contents as a string"), PARSE_OPT_NONEG,
			parse_msg_arg},
		{ OPTION_CALLBACK, 'F', "file", &msg, N_("file"),
			N_("note contents in a file"), PARSE_OPT_NONEG,
			parse_file_arg},
		{ OPTION_CALLBACK, 'c', "reedit-message", &msg, N_("object"),
			N_("reuse and edit specified note object"), PARSE_OPT_NONEG,
			parse_reedit_arg},
		{ OPTION_CALLBACK, 'C', "reuse-message", &msg, N_("object"),
			N_("reuse specified note object"), PARSE_OPT_NONEG,
			parse_reuse_arg},
		OPT_END()
	};
	int edit = !strcmp(argv[0], "edit");

	usage = edit ? git_notes_edit_usage : git_notes_append_usage;
	argc = parse_options(argc, argv, prefix, options, usage,
			     PARSE_OPT_KEEP_ARGV0);

	if (2 < argc) {
		error(_("too many parameters"));
		usage_with_options(usage, options);
	}

	if (msg.given && edit)
		fprintf(stderr, _("The -m/-F/-c/-C options have been deprecated "
			"for the 'edit' subcommand.\n"
			"Please use 'git notes add -f -m/-F/-c/-C' instead.\n"));

	object_ref = 1 < argc ? argv[1] : "HEAD";

	if (get_sha1(object_ref, object))
		die(_("Failed to resolve '%s' as a valid ref."), object_ref);

	t = init_notes_check(argv[0]);
	note = get_note(t, object);

	create_note(object, &msg, !edit, note, new_note);

	if (is_null_sha1(new_note))
		remove_note(t, object);
	else if (add_note(t, object, new_note, combine_notes_overwrite))
		die("BUG: combine_notes_overwrite failed");

	snprintf(logmsg, sizeof(logmsg), "Notes %s by 'git notes %s'",
		 is_null_sha1(new_note) ? "removed" : "added", argv[0]);
	commit_notes(t, logmsg);
	free_notes(t);
	strbuf_release(&(msg.buf));
	return 0;
}