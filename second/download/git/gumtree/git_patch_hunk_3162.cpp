 
 	object_ref = 1 < argc ? argv[1] : "HEAD";
 
 	if (get_sha1(object_ref, object))
 		die(_("Failed to resolve '%s' as a valid ref."), object_ref);
 
-	t = init_notes_check(argv[0]);
+	t = init_notes_check(argv[0], NOTES_INIT_WRITABLE);
 	note = get_note(t, object);
 
 	prepare_note_data(object, &d, edit ? note : NULL);
 
 	if (note && !edit) {
 		/* Append buf to previous note contents */
