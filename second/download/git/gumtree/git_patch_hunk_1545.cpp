 		active_cache_tree = cache_tree();
 
 	if (!cache_tree_fully_valid(active_cache_tree))
 		if (cache_tree_update(&the_index, 0))
 			return error(_("unable to update cache tree\n"));
 
-	return !hashcmp(active_cache_tree->sha1, head_commit->tree->object.oid.hash);
+	return !oidcmp(&active_cache_tree->oid,
+		       &head_commit->tree->object.oid);
 }
 
 static int write_author_script(const char *message)
 {
 	struct strbuf buf = STRBUF_INIT;
 	const char *eol;
