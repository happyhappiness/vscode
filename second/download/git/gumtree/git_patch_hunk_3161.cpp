 
 	object_ref = 1 < argc ? argv[1] : "HEAD";
 
 	if (get_sha1(object_ref, object))
 		die(_("Failed to resolve '%s' as a valid ref."), object_ref);
 
-	t = init_notes_check("copy");
+	t = init_notes_check("copy", NOTES_INIT_WRITABLE);
 	note = get_note(t, object);
 
 	if (note) {
 		if (!force) {
 			retval = error(_("Cannot copy notes. Found existing "
 				       "notes for object %s. Use '-f' to "
