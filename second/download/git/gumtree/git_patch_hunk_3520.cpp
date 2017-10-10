 			if (!sub)
 				die("cache-tree.c: '%.*s' in '%s' not found",
 				    entlen, path + baselen, path);
 			i += sub->count;
 			sha1 = sub->cache_tree->sha1;
 			mode = S_IFDIR;
-			if (sub->cache_tree->entry_count < 0) {
+			contains_ita = sub->cache_tree->entry_count < 0;
+			if (contains_ita) {
 				to_invalidate = 1;
 				expected_missing = 1;
 			}
 		}
 		else {
 			sha1 = ce->sha1;
