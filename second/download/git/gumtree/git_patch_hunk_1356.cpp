 	if (!fill_tree_descriptor(desc + nr - 1, oid->hash))
 		return error(_("Failed to find tree of %s."), oid_to_hex(oid));
 	if (unpack_trees(nr, desc, &opts))
 		return -1;
 
 	if (reset_type == MIXED || reset_type == HARD) {
-		tree = parse_tree_indirect(oid->hash);
+		tree = parse_tree_indirect(oid);
 		prime_cache_tree(&the_index, tree);
 	}
 
 	return 0;
 }
 
