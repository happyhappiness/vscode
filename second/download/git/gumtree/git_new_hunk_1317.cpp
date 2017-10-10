	} else {
		init_notes(NULL, NULL, NULL, NOTES_INIT_WRITABLE);
		t = &default_notes_tree;
	}

	while (strbuf_getline_lf(&buf, stdin) != EOF) {
		struct object_id from_obj, to_obj;
		struct strbuf **split;
		int err;

		split = strbuf_split(&buf, ' ');
		if (!split[0] || !split[1])
			die(_("malformed input line: '%s'."), buf.buf);
		strbuf_rtrim(split[0]);
		strbuf_rtrim(split[1]);
		if (get_oid(split[0]->buf, &from_obj))
			die(_("failed to resolve '%s' as a valid ref."), split[0]->buf);
		if (get_oid(split[1]->buf, &to_obj))
			die(_("failed to resolve '%s' as a valid ref."), split[1]->buf);

		if (rewrite_cmd)
			err = copy_note_for_rewrite(c, &from_obj, &to_obj);
		else
			err = copy_note(t, &from_obj, &to_obj, force,
					combine_notes_overwrite);

		if (err) {
			error(_("failed to copy notes from '%s' to '%s'"),
			      split[0]->buf, split[1]->buf);
			ret = 1;
