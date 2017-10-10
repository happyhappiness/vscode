 		return error("%s: cannot add to the index - missing --add option?",
 			     path);
 	report("add '%s'", path);
 	return 0;
 }
 
-static void chmod_path(int flip, const char *path)
+static void chmod_path(char flip, const char *path)
 {
 	int pos;
 	struct cache_entry *ce;
-	unsigned int mode;
 
 	pos = cache_name_pos(path, strlen(path));
 	if (pos < 0)
 		goto fail;
 	ce = active_cache[pos];
-	mode = ce->ce_mode;
-	if (!S_ISREG(mode))
+	if (chmod_cache_entry(ce, flip) < 0)
 		goto fail;
-	switch (flip) {
-	case '+':
-		ce->ce_mode |= 0111; break;
-	case '-':
-		ce->ce_mode &= ~0111; break;
-	default:
-		goto fail;
-	}
-	cache_tree_invalidate_path(&the_index, path);
-	ce->ce_flags |= CE_UPDATE_IN_BASE;
-	active_cache_changed |= CE_ENTRY_CHANGED;
+
 	report("chmod %cx '%s'", flip, path);
 	return;
  fail:
 	die("git update-index: cannot chmod %cx '%s'", flip, path);
 }
 
