		fprintf(stderr, _("Overwriting existing notes for object %s\n"),
			sha1_to_hex(object));
	}

	from_note = get_note(t, from_obj);
	if (!from_note) {
		retval = error(_("Missing notes on source object %s. Cannot "
			       "copy."), sha1_to_hex(from_obj));
		goto out;
	}

	if (add_note(t, object, from_note, combine_notes_overwrite))
		die("BUG: combine_notes_overwrite failed");
