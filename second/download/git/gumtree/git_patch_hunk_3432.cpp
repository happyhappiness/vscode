 		if (ret < 1)
 			continue;
 
 		id = new_rerere_id(sha1);
 		string_list_insert(rr, path)->util = id;
 
-		/*
-		 * If the directory does not exist, create
-		 * it.  mkdir_in_gitdir() will fail with
-		 * EEXIST if there already is one.
-		 *
-		 * NEEDSWORK: make sure "gc" does not remove
-		 * preimage without removing the directory.
-		 */
-		if (mkdir_in_gitdir(rerere_path(id, NULL)))
-			continue;
-
-		/*
-		 * We are the first to encounter this
-		 * conflict.  Ask handle_file() to write the
-		 * normalized contents to the "preimage" file.
-		 */
-		handle_file(path, NULL, rerere_path(id, "preimage"));
-		fprintf(stderr, "Recorded preimage for '%s'\n", path);
+		/* Ensure that the directory exists. */
+		mkdir_in_gitdir(rerere_path(id, NULL));
 	}
 
 	for (i = 0; i < rr->nr; i++)
 		do_rerere_one_path(&rr->items[i], &update);
 
 	if (update.nr)
