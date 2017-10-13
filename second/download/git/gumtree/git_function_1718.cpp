tatic int add(int argc, const char **argv, const char *prefix)
{
	int retval = 0, force = 0;
	const char *object_ref;
	struct notes_tree *t;
	unsigned char object[20], new_note[20];
	char logmsg[100];
	const unsigned char *note;
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
		OPT__FORCE(&force, N_("replace existing notes")),
		OPT_END()
	};

	argc = parse_options(argc, argv, prefix, options, git_notes_add_usage,
			     PARSE_OPT_KEEP_ARGV0);

	if (2 < argc) {
		error(_("too many parameters"));
		usage_with_options(git_notes_add_usage, options);
	}

	object_ref = argc > 1 ? argv[1] : "HEAD";

	if (get_sha1(object_ref, object))
		die(_("Failed to resolve '%s' as a valid ref."), object_ref);

	t = init_notes_check("add");
	note = get_note(t, object);

	if (note) {
		if (!force) {
			if (!msg.given) {
				/*
				 * Redirect to "edit" subcommand.
				 *
				 * We only end up here if none of -m/-F/-c/-C
				 * or -f are given. The original args are
				 * therefore still in argv[0-1].
				 */
				argv[0] = "edit";
				free_notes(t);
				return append_edit(argc, argv, prefix);
			}
			retval = error(_("Cannot add notes. Found existing notes "
				       "for object %s. Use '-f' to overwrite "
				       "existing notes"), sha1_to_hex(object));
			goto out;
		}
		fprintf(stderr, _("Overwriting existing notes for object %s\n"),
			sha1_to_hex(object));
	}

	create_note(object, &msg, 0, note, new_note);

	if (is_null_sha1(new_note))
		remove_note(t, object);
	else if (add_note(t, object, new_note, combine_notes_overwrite))
		die("BUG: combine_notes_overwrite failed");

	snprintf(logmsg, sizeof(logmsg), "Notes %s by 'git notes %s'",
		 is_null_sha1(new_note) ? "removed" : "added", "add");
	commit_notes(t, logmsg);
out:
	free_notes(t);
	strbuf_release(&(msg.buf));
	return retval;
}