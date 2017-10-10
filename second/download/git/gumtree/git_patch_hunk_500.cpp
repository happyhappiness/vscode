 		pathspec->nr = 1;
 		pathspec->_raw = raw;
 		return;
 	}
 
 	n = 0;
-	while (argv[n])
+	warn_empty_string = 1;
+	while (argv[n]) {
+		if (*argv[n] == '\0' && warn_empty_string) {
+			warning(_("empty strings as pathspecs will be made invalid in upcoming releases. "
+				  "please use . instead if you meant to match all paths"));
+			warn_empty_string = 0;
+		}
 		n++;
+	}
 
 	pathspec->nr = n;
 	ALLOC_ARRAY(pathspec->items, n);
 	item = pathspec->items;
 	pathspec->_raw = argv;
 	prefixlen = prefix ? strlen(prefix) : 0;
