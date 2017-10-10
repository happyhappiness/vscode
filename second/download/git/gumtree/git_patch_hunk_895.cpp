 				strbuf_addstr(&buf, "-dirty");
 			add_left_or_right(&submodules, dst_path, buf.buf, 1);
 			continue;
 		}
 
 		if (S_ISLNK(lmode)) {
-			char *content = read_sha1_file(loid.hash, &type, &size);
+			char *content = get_symlink(&loid, src_path);
 			add_left_or_right(&symlinks2, src_path, content, 0);
 			free(content);
 		}
 
 		if (S_ISLNK(rmode)) {
-			char *content = read_sha1_file(roid.hash, &type, &size);
+			char *content = get_symlink(&roid, dst_path);
 			add_left_or_right(&symlinks2, dst_path, content, 1);
 			free(content);
 		}
 
 		if (lmode && status != 'C') {
-			ce->ce_mode = lmode;
-			oidcpy(&ce->oid, &loid);
-			strcpy(ce->name, src_path);
-			ce->ce_namelen = src_path_len;
-			if (checkout_entry(ce, &lstate, NULL))
+			if (checkout_path(lmode, &loid, src_path, &lstate))
 				return error("could not write '%s'", src_path);
 		}
 
-		if (rmode) {
+		if (rmode && !S_ISLNK(rmode)) {
 			struct working_tree_entry *entry;
 
 			/* Avoid duplicate working_tree entries */
 			FLEX_ALLOC_STR(entry, path, dst_path);
 			hashmap_entry_init(entry, strhash(dst_path));
 			if (hashmap_get(&working_tree_dups, entry, NULL)) {
 				free(entry);
 				continue;
 			}
 			hashmap_add(&working_tree_dups, entry);
 
 			if (!use_wt_file(workdir, dst_path, &roid)) {
-				ce->ce_mode = rmode;
-				oidcpy(&ce->oid, &roid);
-				strcpy(ce->name, dst_path);
-				ce->ce_namelen = dst_path_len;
-				if (checkout_entry(ce, &rstate, NULL))
+				if (checkout_path(rmode, &roid, dst_path, &rstate))
 					return error("could not write '%s'",
 						     dst_path);
 			} else if (!is_null_oid(&roid)) {
 				/*
 				 * Changes in the working tree need special
 				 * treatment since they are not part of the
