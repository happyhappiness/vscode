 	if (argc > 0) {
 		int j = 0;
 		int i;
 		refs = xcalloc(argc + 1, sizeof(const char *));
 		for (i = 0; i < argc; i++) {
 			if (!strcmp(argv[i], "tag")) {
-				char *ref;
 				i++;
 				if (i >= argc)
 					die(_("You need to specify a tag name."));
-				ref = xmalloc(strlen(argv[i]) * 2 + 22);
-				strcpy(ref, "refs/tags/");
-				strcat(ref, argv[i]);
-				strcat(ref, ":refs/tags/");
-				strcat(ref, argv[i]);
-				refs[j++] = ref;
+				refs[j++] = xstrfmt("refs/tags/%s:refs/tags/%s",
+						    argv[i], argv[i]);
 			} else
 				refs[j++] = argv[i];
 		}
 		refs[j] = NULL;
 		ref_nr = j;
 	}
