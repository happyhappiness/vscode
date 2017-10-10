 		fprintf(stderr, _("The -m/-F/-c/-C options have been deprecated "
 			"for the 'edit' subcommand.\n"
 			"Please use 'git notes add -f -m/-F/-c/-C' instead.\n"));
 
 	object_ref = 1 < argc ? argv[1] : "HEAD";
 
-	if (get_sha1(object_ref, object))
+	if (get_oid(object_ref, &object))
 		die(_("failed to resolve '%s' as a valid ref."), object_ref);
 
 	t = init_notes_check(argv[0], NOTES_INIT_WRITABLE);
-	note = get_note(t, object);
+	note = get_note(t, &object);
 
-	prepare_note_data(object, &d, edit ? note : NULL);
+	prepare_note_data(&object, &d, edit && note ? note->hash : NULL);
 
 	if (note && !edit) {
 		/* Append buf to previous note contents */
 		unsigned long size;
 		enum object_type type;
-		char *prev_buf = read_sha1_file(note, &type, &size);
+		char *prev_buf = read_sha1_file(note->hash, &type, &size);
 
 		strbuf_grow(&d.buf, size + 1);
 		if (d.buf.len && prev_buf && size)
 			strbuf_insert(&d.buf, 0, "\n", 1);
 		if (prev_buf && size)
 			strbuf_insert(&d.buf, 0, prev_buf, size);
 		free(prev_buf);
 	}
 
 	if (d.buf.len || allow_empty) {
-		write_note_data(&d, new_note);
-		if (add_note(t, object, new_note, combine_notes_overwrite))
+		write_note_data(&d, new_note.hash);
+		if (add_note(t, &object, &new_note, combine_notes_overwrite))
 			die("BUG: combine_notes_overwrite failed");
 		logmsg = xstrfmt("Notes added by 'git notes %s'", argv[0]);
 	} else {
 		fprintf(stderr, _("Removing note for object %s\n"),
-			sha1_to_hex(object));
-		remove_note(t, object);
+			oid_to_hex(&object));
+		remove_note(t, object.hash);
 		logmsg = xstrfmt("Notes removed by 'git notes %s'", argv[0]);
 	}
 	commit_notes(t, logmsg);
 
 	free(logmsg);
 	free_note_data(&d);
