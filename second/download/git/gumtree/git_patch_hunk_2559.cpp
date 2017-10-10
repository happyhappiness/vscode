 			warning("'git rerere forget' without paths is deprecated");
 		parse_pathspec(&pathspec, 0, PATHSPEC_PREFER_CWD,
 			       prefix, argv + 1);
 		return rerere_forget(&pathspec);
 	}
 
-	fd = setup_rerere(&merge_rr, flags);
-	if (fd < 0)
-		return 0;
-
 	if (!strcmp(argv[0], "clear")) {
 		rerere_clear(&merge_rr);
 	} else if (!strcmp(argv[0], "gc"))
 		rerere_gc(&merge_rr);
-	else if (!strcmp(argv[0], "status"))
+	else if (!strcmp(argv[0], "status")) {
+		if (setup_rerere(&merge_rr, flags | RERERE_READONLY) < 0)
+			return 0;
 		for (i = 0; i < merge_rr.nr; i++)
 			printf("%s\n", merge_rr.items[i].string);
-	else if (!strcmp(argv[0], "remaining")) {
+	} else if (!strcmp(argv[0], "remaining")) {
 		rerere_remaining(&merge_rr);
 		for (i = 0; i < merge_rr.nr; i++) {
 			if (merge_rr.items[i].util != RERERE_RESOLVED)
 				printf("%s\n", merge_rr.items[i].string);
 			else
 				/* prepare for later call to
 				 * string_list_clear() */
 				merge_rr.items[i].util = NULL;
 		}
-	} else if (!strcmp(argv[0], "diff"))
+	} else if (!strcmp(argv[0], "diff")) {
+		if (setup_rerere(&merge_rr, flags | RERERE_READONLY) < 0)
+			return 0;
 		for (i = 0; i < merge_rr.nr; i++) {
 			const char *path = merge_rr.items[i].string;
 			const char *name = (const char *)merge_rr.items[i].util;
-			if (diff_two(rerere_path(name, "preimage"), path, path, path))
-				die("unable to generate diff for %s", name);
+			diff_two(rerere_path(name, "preimage"), path, path, path);
 		}
-	else
+	} else
 		usage_with_options(rerere_usage, options);
 
 	string_list_clear(&merge_rr, 1);
 	return 0;
 }
