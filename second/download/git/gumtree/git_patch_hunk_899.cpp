 		int saved_dcctc = 0;
 
 		if (opt->diffopt.detect_rename)
 			opt->diffopt.setup |= (DIFF_SETUP_USE_SIZE_CACHE |
 					       DIFF_SETUP_USE_CACHE);
 		while (fgets(line, sizeof(line), stdin)) {
-			unsigned char sha1[20];
+			struct object_id oid;
 
-			if (get_sha1_hex(line, sha1)) {
+			if (get_oid_hex(line, &oid)) {
 				fputs(line, stdout);
 				fflush(stdout);
 			}
 			else {
 				diff_tree_stdin(line);
 				if (saved_nrl < opt->diffopt.needed_rename_limit)
