
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

static int show(int argc, const char **argv, const char *prefix)
{
	const char *object_ref;
