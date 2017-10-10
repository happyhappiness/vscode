 	}
 	if (2 < argc) {
 		error(_("too many parameters"));
 		usage_with_options(git_notes_copy_usage, options);
 	}
 
-	if (get_sha1(argv[0], from_obj))
+	if (get_oid(argv[0], &from_obj))
 		die(_("failed to resolve '%s' as a valid ref."), argv[0]);
 
 	object_ref = 1 < argc ? argv[1] : "HEAD";
 
-	if (get_sha1(object_ref, object))
+	if (get_oid(object_ref, &object))
 		die(_("failed to resolve '%s' as a valid ref."), object_ref);
 
 	t = init_notes_check("copy", NOTES_INIT_WRITABLE);
-	note = get_note(t, object);
+	note = get_note(t, &object);
 
 	if (note) {
 		if (!force) {
 			retval = error(_("Cannot copy notes. Found existing "
 				       "notes for object %s. Use '-f' to "
 				       "overwrite existing notes"),
-				       sha1_to_hex(object));
+				       oid_to_hex(&object));
 			goto out;
 		}
 		fprintf(stderr, _("Overwriting existing notes for object %s\n"),
-			sha1_to_hex(object));
+			oid_to_hex(&object));
 	}
 
-	from_note = get_note(t, from_obj);
+	from_note = get_note(t, &from_obj);
 	if (!from_note) {
 		retval = error(_("missing notes on source object %s. Cannot "
-			       "copy."), sha1_to_hex(from_obj));
+			       "copy."), oid_to_hex(&from_obj));
 		goto out;
 	}
 
-	if (add_note(t, object, from_note, combine_notes_overwrite))
+	if (add_note(t, &object, from_note, combine_notes_overwrite))
 		die("BUG: combine_notes_overwrite failed");
 	commit_notes(t, "Notes added by 'git notes copy'");
 out:
 	free_notes(t);
 	return retval;
 }
 
 static int append_edit(int argc, const char **argv, const char *prefix)
 {
 	int allow_empty = 0;
 	const char *object_ref;
 	struct notes_tree *t;
-	unsigned char object[20], new_note[20];
-	const unsigned char *note;
+	struct object_id object, new_note;
+	const struct object_id *note;
 	char *logmsg;
 	const char * const *usage;
 	struct note_data d = { 0, 0, NULL, STRBUF_INIT };
 	struct option options[] = {
 		{ OPTION_CALLBACK, 'm', "message", &d, N_("message"),
 			N_("note contents as a string"), PARSE_OPT_NONEG,
