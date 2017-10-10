 
 	if (1 < argc) {
 		error(_("too many parameters"));
 		usage_with_options(git_notes_list_usage, options);
 	}
 
-	t = init_notes_check("list");
+	t = init_notes_check("list", 0);
 	if (argc) {
 		if (get_sha1(argv[0], object))
 			die(_("Failed to resolve '%s' as a valid ref."), argv[0]);
 		note = get_note(t, object);
 		if (note) {
 			puts(sha1_to_hex(note));
