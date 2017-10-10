 
 	t = init_notes_check("add");
 	note = get_note(t, object);
 
 	if (note) {
 		if (!force) {
-			if (!msg.given) {
-				/*
-				 * Redirect to "edit" subcommand.
-				 *
-				 * We only end up here if none of -m/-F/-c/-C
-				 * or -f are given. The original args are
-				 * therefore still in argv[0-1].
-				 */
-				argv[0] = "edit";
-				free_notes(t);
-				return append_edit(argc, argv, prefix);
+			free_notes(t);
+			if (d.given) {
+				free_note_data(&d);
+				return error(_("Cannot add notes. "
+					"Found existing notes for object %s. "
+					"Use '-f' to overwrite existing notes"),
+					sha1_to_hex(object));
 			}
-			retval = error(_("Cannot add notes. Found existing notes "
-				       "for object %s. Use '-f' to overwrite "
-				       "existing notes"), sha1_to_hex(object));
-			goto out;
+			/*
+			 * Redirect to "edit" subcommand.
+			 *
+			 * We only end up here if none of -m/-F/-c/-C or -f are
+			 * given. The original args are therefore still in
+			 * argv[0-1].
+			 */
+			argv[0] = "edit";
+			return append_edit(argc, argv, prefix);
 		}
 		fprintf(stderr, _("Overwriting existing notes for object %s\n"),
 			sha1_to_hex(object));
 	}
 
-	create_note(object, &msg, 0, note, new_note);
-
-	if (is_null_sha1(new_note))
+	prepare_note_data(object, &d, note);
+	if (d.buf.len || allow_empty) {
+		write_note_data(&d, new_note);
+		if (add_note(t, object, new_note, combine_notes_overwrite))
+			die("BUG: combine_notes_overwrite failed");
+		commit_notes(t, "Notes added by 'git notes add'");
+	} else {
+		fprintf(stderr, _("Removing note for object %s\n"),
+			sha1_to_hex(object));
 		remove_note(t, object);
-	else if (add_note(t, object, new_note, combine_notes_overwrite))
-		die("BUG: combine_notes_overwrite failed");
+		commit_notes(t, "Notes removed by 'git notes add'");
+	}
 
-	snprintf(logmsg, sizeof(logmsg), "Notes %s by 'git notes %s'",
-		 is_null_sha1(new_note) ? "removed" : "added", "add");
-	commit_notes(t, logmsg);
-out:
+	free_note_data(&d);
 	free_notes(t);
-	strbuf_release(&(msg.buf));
-	return retval;
+	return 0;
 }
 
 static int copy(int argc, const char **argv, const char *prefix)
 {
 	int retval = 0, force = 0, from_stdin = 0;
 	const unsigned char *from_note, *note;
