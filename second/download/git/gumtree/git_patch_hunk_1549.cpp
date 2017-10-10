 		/*
 		 * We do not intend to commit immediately.  We just want to
 		 * merge the differences in, so let's compute the tree
 		 * that represents the "current" state for merge-recursive
 		 * to work on.
 		 */
-		if (write_cache_as_tree(head, 0, NULL))
+		if (write_cache_as_tree(head.hash, 0, NULL))
 			return error(_("your index file is unmerged."));
 	} else {
-		unborn = get_sha1("HEAD", head);
+		unborn = get_oid("HEAD", &head);
 		if (unborn)
-			hashcpy(head, EMPTY_TREE_SHA1_BIN);
+			oidcpy(&head, &empty_tree_oid);
 		if (index_differs_from(unborn ? EMPTY_TREE_SHA1_HEX : "HEAD", 0, 0))
 			return error_dirty_index(opts);
 	}
 	discard_cache();
 
 	if (!commit->parents)
