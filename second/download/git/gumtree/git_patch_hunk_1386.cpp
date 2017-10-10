 			entlen = slash - (path + baselen);
 			sub = find_subtree(it, path + baselen, entlen, 0);
 			if (!sub)
 				die("cache-tree.c: '%.*s' in '%s' not found",
 				    entlen, path + baselen, path);
 			i += sub->count;
-			sha1 = sub->cache_tree->sha1;
+			sha1 = sub->cache_tree->oid.hash;
 			mode = S_IFDIR;
 			contains_ita = sub->cache_tree->entry_count < 0;
 			if (contains_ita) {
 				to_invalidate = 1;
 				expected_missing = 1;
 			}
