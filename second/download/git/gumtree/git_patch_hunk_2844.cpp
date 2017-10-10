 		break;
 	}
 
 	if (argv[i]) {
 		int j;
 		pattern = xcalloc(argc - i + 1, sizeof(const char *));
-		for (j = i; j < argc; j++) {
-			int len = strlen(argv[j]);
-			char *p = xmalloc(len + 3);
-			sprintf(p, "*/%s", argv[j]);
-			pattern[j - i] = p;
-		}
+		for (j = i; j < argc; j++)
+			pattern[j - i] = xstrfmt("*/%s", argv[j]);
 	}
 	remote = remote_get(dest);
 	if (!remote) {
 		if (dest)
 			die("bad repository '%s'", dest);
 		die("No remote configured to list refs from.");
