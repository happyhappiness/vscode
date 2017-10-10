 		die("broken index, expect %s in %s, got %s",
 		    sha1_to_hex(split_index->base_sha1),
 		    git_path("sharedindex.%s",
 			     sha1_to_hex(split_index->base_sha1)),
 		    sha1_to_hex(split_index->base->sha1));
 	merge_base_index(istate);
-	check_ce_order(istate);
+	post_read_index_from(istate);
 	return ret;
 }
 
 int is_index_unborn(struct index_state *istate)
 {
 	return (!istate->cache_nr && !istate->timestamp.sec);
