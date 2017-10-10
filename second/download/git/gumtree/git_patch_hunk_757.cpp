 
 	/* die if we replaced an object with one that does not exist */
 	if (repl != sha1)
 		die("replacement %s not found for %s",
 		    sha1_to_hex(repl), sha1_to_hex(sha1));
 
-	if (has_loose_object(repl)) {
-		const char *path = sha1_file_name(sha1);
-
+	if (!stat_sha1_file(repl, &st, &path))
 		die("loose object %s (stored in %s) is corrupt",
 		    sha1_to_hex(repl), path);
-	}
 
 	if ((p = has_packed_and_bad(repl)) != NULL)
 		die("packed object %s (stored in %s) is corrupt",
 		    sha1_to_hex(repl), p->pack_name);
 
 	return NULL;
