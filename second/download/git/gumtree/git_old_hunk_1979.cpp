
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

static int copy(int argc, const char **argv, const char *prefix)
{
	int retval = 0, force = 0, from_stdin = 0;
	const unsigned char *from_note, *note;
