 	}
 
 	if (!active_cache_tree)
 		active_cache_tree = cache_tree();
 
 	if (!cache_tree_fully_valid(active_cache_tree) &&
-	    cache_tree_update(active_cache_tree,
-			      (const struct cache_entry * const *)active_cache,
-			      active_nr, 0) < 0)
+	    cache_tree_update(&the_index, 0) < 0)
 		die(_("error building trees"));
 
 	result = lookup_tree(active_cache_tree->sha1);
 
 	return result;
 }
