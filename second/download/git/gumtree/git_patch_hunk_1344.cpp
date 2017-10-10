 	}
 	resolve_undo_clear();
 
 	for (i = 0; i < argc; i++) {
 		const char *arg = argv[i];
 
-		if (get_sha1(arg, sha1))
+		if (get_oid(arg, &oid))
 			die("Not a valid object name %s", arg);
-		if (list_tree(sha1) < 0)
+		if (list_tree(&oid) < 0)
 			die("failed to unpack tree object %s", arg);
 		stage++;
 	}
 	if (!nr_trees && !read_empty && !opts.merge)
 		warning("read-tree: emptying the index with no arguments is deprecated; use --empty");
 	else if (nr_trees > 0 && read_empty)
