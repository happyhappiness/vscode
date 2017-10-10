 }
 
 static int add_cacheinfo(unsigned int mode, const unsigned char *sha1,
 		const char *path, int stage, int refresh, int options)
 {
 	struct cache_entry *ce;
-	ce = make_cache_entry(mode, sha1 ? sha1 : null_sha1, path, stage,
-			      (refresh ? (CE_MATCH_REFRESH |
-					  CE_MATCH_IGNORE_MISSING) : 0 ));
+	int ret;
+
+	ce = make_cache_entry(mode, sha1 ? sha1 : null_sha1, path, stage, 0);
 	if (!ce)
 		return error(_("addinfo_cache failed for path '%s'"), path);
-	return add_cache_entry(ce, options);
+
+	ret = add_cache_entry(ce, options);
+	if (refresh) {
+		struct cache_entry *nce;
+
+		nce = refresh_cache_entry(ce, CE_MATCH_REFRESH | CE_MATCH_IGNORE_MISSING);
+		if (nce != ce)
+			ret = add_cache_entry(nce, options);
+	}
+	return ret;
 }
 
 static void init_tree_desc_from_tree(struct tree_desc *desc, struct tree *tree)
 {
 	parse_tree(tree);
 	init_tree_desc(desc, tree->buffer, tree->size);
