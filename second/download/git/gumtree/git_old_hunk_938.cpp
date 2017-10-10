	}

	if (d.buf.len || allow_empty) {
		write_note_data(&d, new_note);
		if (add_note(t, object, new_note, combine_notes_overwrite))
			die("BUG: combine_notes_overwrite failed");
		snprintf(logmsg, sizeof(logmsg), "Notes added by 'git notes %s'",
			argv[0]);
	} else {
		fprintf(stderr, _("Removing note for object %s\n"),
			sha1_to_hex(object));
		remove_note(t, object);
		snprintf(logmsg, sizeof(logmsg), "Notes removed by 'git notes %s'",
			argv[0]);
	}
	commit_notes(t, logmsg);

	free_note_data(&d);
	free_notes(t);
	return 0;
}

static int show(int argc, const char **argv, const char *prefix)
