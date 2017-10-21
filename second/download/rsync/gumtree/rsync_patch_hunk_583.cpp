 
 	if (am_root) {
 		p = lp_uid(i);
 		if (!name_to_uid(p, &uid)) {
 			if (!isdigit(*p)) {
 				rprintf(FERROR,"Invalid uid %s\n", p);
-				io_printf(fd,"@ERROR: invalid uid\n");
+				io_printf(fd,"@ERROR: invalid uid %s\n", p);
 				return -1;
 			} 
 			uid = atoi(p);
 		}
 
 		p = lp_gid(i);
 		if (!name_to_gid(p, &gid)) {
 			if (!isdigit(*p)) {
 				rprintf(FERROR,"Invalid gid %s\n", p);
-				io_printf(fd,"@ERROR: invalid gid\n");
+				io_printf(fd,"@ERROR: invalid gid %s\n", p);
 				return -1;
 			} 
 			gid = atoi(p);
 		}
 	}
+        
+        /* TODO: If we're not root, but the configuration requests
+         * that we change to some uid other than the current one, then
+         * log a warning. */
+
+        /* TODO: Perhaps take a list of gids, and make them into the
+         * supplementary groups. */
 
 	p = lp_include_from(i);
 	add_exclude_file(p, 1, 1);
 
 	p = lp_include(i);
 	add_include_line(p);
