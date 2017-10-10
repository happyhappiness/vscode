 		pattern = NULL;
 
 	if (verify) {
 		if (!pattern)
 			die("--verify requires a reference");
 		while (*pattern) {
-			unsigned char sha1[20];
+			struct object_id oid;
 
 			if (starts_with(*pattern, "refs/") &&
-			    !read_ref(*pattern, sha1)) {
+			    !read_ref(*pattern, oid.hash)) {
 				if (!quiet)
-					show_one(*pattern, sha1);
+					show_one(*pattern, &oid);
 			}
 			else if (!quiet)
 				die("'%s' - not a valid ref", *pattern);
 			else
 				return 1;
 			pattern++;
