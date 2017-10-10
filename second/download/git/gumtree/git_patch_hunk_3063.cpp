 			prune = PRUNE_BY_DEFAULT;
 	}
 
 	if (argc > 0) {
 		int j = 0;
 		int i;
-		refs = xcalloc(argc + 1, sizeof(const char *));
+		refs = xcalloc(st_add(argc, 1), sizeof(const char *));
 		for (i = 0; i < argc; i++) {
 			if (!strcmp(argv[i], "tag")) {
 				i++;
 				if (i >= argc)
 					die(_("You need to specify a tag name."));
 				refs[j++] = xstrfmt("refs/tags/%s:refs/tags/%s",
