 		return -1;
 
 	if (!active_cache_tree)
 		active_cache_tree = cache_tree();
 
 	if (!cache_tree_fully_valid(active_cache_tree))
-		if (cache_tree_update(active_cache_tree,
-				      (const struct cache_entry * const *)active_cache,
-				      active_nr, 0))
+		if (cache_tree_update(&the_index, 0))
 			return error(_("Unable to update cache tree\n"));
 
 	return !hashcmp(active_cache_tree->sha1, head_commit->tree->object.sha1);
 }
 
 /*
