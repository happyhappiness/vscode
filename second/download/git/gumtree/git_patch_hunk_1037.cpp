 	}
 
 	if (split_index->base)
 		discard_index(split_index->base);
 	else
 		split_index->base = xcalloc(1, sizeof(*split_index->base));
-	ret = do_read_index(split_index->base,
-			    git_path("sharedindex.%s",
-				     sha1_to_hex(split_index->base_sha1)), 1);
+
+	base_sha1_hex = sha1_to_hex(split_index->base_sha1);
+	base_path = git_path("sharedindex.%s", base_sha1_hex);
+	ret = do_read_index(split_index->base, base_path, 1);
 	if (hashcmp(split_index->base_sha1, split_index->base->sha1))
 		die("broken index, expect %s in %s, got %s",
-		    sha1_to_hex(split_index->base_sha1),
-		    git_path("sharedindex.%s",
-			     sha1_to_hex(split_index->base_sha1)),
+		    base_sha1_hex, base_path,
 		    sha1_to_hex(split_index->base->sha1));
+
+	freshen_shared_index(base_sha1_hex, 0);
 	merge_base_index(istate);
 	post_read_index_from(istate);
 	return ret;
 }
 
 int is_index_unborn(struct index_state *istate)
