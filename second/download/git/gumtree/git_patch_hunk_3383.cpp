 	read_cache();
 	for (i = 0; i < active_nr; i++) {
 		struct cache_entry *ce = active_cache[i];
 		struct stat st;
 
 		if (lstat(ce->name, &st)) {
-			error("lstat(%s): %s", ce->name, strerror(errno));
+			error_errno("lstat(%s)", ce->name);
 			continue;
 		}
 
 		if (ce_match_stat(ce, &st, 0))
 			dirty++;
 		else if (ce_match_stat(ce, &st, CE_MATCH_RACY_IS_DIRTY))
