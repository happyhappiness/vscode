 	strbuf_add(&path, base, baselen);
 	strbuf_addstr(&path, filename);
 	if (S_ISDIR(mode) || S_ISGITLINK(mode))
 		strbuf_addch(&path, '/');
 	path_without_prefix = path.buf + args->baselen;
 
-	setup_archive_check(check);
-	if (!git_check_attr(path_without_prefix, ARRAY_SIZE(check), check)) {
-		if (ATTR_TRUE(check[0].value))
+	if (!check)
+		check = attr_check_initl("export-ignore", "export-subst", NULL);
+	if (!git_check_attr(path_without_prefix, check)) {
+		if (ATTR_TRUE(check->items[0].value))
 			return 0;
-		args->convert = ATTR_TRUE(check[1].value);
+		args->convert = ATTR_TRUE(check->items[1].value);
 	}
 
 	if (S_ISDIR(mode) || S_ISGITLINK(mode)) {
 		if (args->verbose)
 			fprintf(stderr, "%.*s\n", (int)path.len, path.buf);
 		err = write_entry(args, sha1, path.buf, path.len, mode);
