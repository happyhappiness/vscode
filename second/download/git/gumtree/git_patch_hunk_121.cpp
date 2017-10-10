 		return error(_("Failed to find tree of %s."), sha1_to_hex(sha1));
 	if (unpack_trees(nr, desc, &opts))
 		return -1;
 
 	if (reset_type == MIXED || reset_type == HARD) {
 		tree = parse_tree_indirect(sha1);
-		prime_cache_tree(&active_cache_tree, tree);
+		prime_cache_tree(&the_index, tree);
 	}
 
 	return 0;
 }
 
 static void print_new_head_line(struct commit *commit)
