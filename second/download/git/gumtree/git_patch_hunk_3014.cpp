 		active_cache_tree = cache_tree();
 
 	if (!cache_tree_fully_valid(active_cache_tree))
 		if (cache_tree_update(&the_index, 0))
 			return error(_("Unable to update cache tree\n"));
 
-	return !hashcmp(active_cache_tree->sha1, head_commit->tree->object.sha1);
+	return !hashcmp(active_cache_tree->sha1, head_commit->tree->object.oid.hash);
 }
 
 /*
  * If we are cherry-pick, and if the merge did not result in
  * hand-editing, we will hit this commit and inherit the original
  * author date and name.
