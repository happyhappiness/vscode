 			char *content = get_symlink(&roid, dst_path);
 			add_left_or_right(&symlinks2, dst_path, content, 1);
 			free(content);
 		}
 
 		if (lmode && status != 'C') {
-			if (checkout_path(lmode, &loid, src_path, &lstate))
-				return error("could not write '%s'", src_path);
+			if (checkout_path(lmode, &loid, src_path, &lstate)) {
+				ret = error("could not write '%s'", src_path);
+				goto finish;
+			}
 		}
 
 		if (rmode && !S_ISLNK(rmode)) {
 			struct working_tree_entry *entry;
 
 			/* Avoid duplicate working_tree entries */
