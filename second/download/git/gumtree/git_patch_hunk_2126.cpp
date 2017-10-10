 		die(_("--index outside a repository"));
 	if (cached) {
 		if (is_not_gitdir)
 			die(_("--cached outside a repository"));
 		check_index = 1;
 	}
+	if (check_index)
+		unsafe_paths = 0;
+
 	for (i = 0; i < argc; i++) {
 		const char *arg = argv[i];
 		int fd;
 
 		if (!strcmp(arg, "-")) {
 			errs |= apply_patch(0, "<stdin>", options);
