 
 	if (2 < argc) {
 		error(_("too many parameters"));
 		usage_with_options(usage, options);
 	}
 
-	if (msg.given && edit)
+	if (d.given && edit)
 		fprintf(stderr, _("The -m/-F/-c/-C options have been deprecated "
 			"for the 'edit' subcommand.\n"
 			"Please use 'git notes add -f -m/-F/-c/-C' instead.\n"));
 
 	object_ref = 1 < argc ? argv[1] : "HEAD";
 
 	if (get_sha1(object_ref, object))
 		die(_("Failed to resolve '%s' as a valid ref."), object_ref);
 
 	t = init_notes_check(argv[0]);
 	note = get_note(t, object);
 
-	create_note(object, &msg, !edit, note, new_note);
+	prepare_note_data(object, &d, edit ? note : NULL);
 
-	if (is_null_sha1(new_note))
-		remove_note(t, object);
-	else if (add_note(t, object, new_note, combine_notes_overwrite))
-		die("BUG: combine_notes_overwrite failed");
+	if (note && !edit) {
+		/* Append buf to previous note contents */
+		unsigned long size;
+		enum object_type type;
+		char *prev_buf = read_sha1_file(note, &type, &size);
+
+		strbuf_grow(&d.buf, size + 1);
+		if (d.buf.len && prev_buf && size)
+			strbuf_insert(&d.buf, 0, "\n", 1);
+		if (prev_buf && size)
+			strbuf_insert(&d.buf, 0, prev_buf, size);
+		free(prev_buf);
+	}
 
-	snprintf(logmsg, sizeof(logmsg), "Notes %s by 'git notes %s'",
-		 is_null_sha1(new_note) ? "removed" : "added", argv[0]);
+	if (d.buf.len || allow_empty) {
+		write_note_data(&d, new_note);
+		if (add_note(t, object, new_note, combine_notes_overwrite))
+			die("BUG: combine_notes_overwrite failed");
+		snprintf(logmsg, sizeof(logmsg), "Notes added by 'git notes %s'",
+			argv[0]);
+	} else {
+		fprintf(stderr, _("Removing note for object %s\n"),
+			sha1_to_hex(object));
+		remove_note(t, object);
+		snprintf(logmsg, sizeof(logmsg), "Notes removed by 'git notes %s'",
+			argv[0]);
+	}
 	commit_notes(t, logmsg);
+
+	free_note_data(&d);
 	free_notes(t);
-	strbuf_release(&(msg.buf));
 	return 0;
 }
 
 static int show(int argc, const char **argv, const char *prefix)
 {
 	const char *object_ref;
