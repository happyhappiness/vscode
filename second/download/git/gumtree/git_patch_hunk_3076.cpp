 static int module_list_compute(int argc, const char **argv,
 			       const char *prefix,
 			       struct pathspec *pathspec,
 			       struct module_list *list)
 {
 	int i, result = 0;
-	char *max_prefix, *ps_matched = NULL;
-	int max_prefix_len;
+	char *ps_matched = NULL;
 	parse_pathspec(pathspec, 0,
 		       PATHSPEC_PREFER_FULL |
 		       PATHSPEC_STRIP_SUBMODULE_SLASH_CHEAP,
 		       prefix, argv);
 
-	/* Find common prefix for all pathspec's */
-	max_prefix = common_prefix(pathspec);
-	max_prefix_len = max_prefix ? strlen(max_prefix) : 0;
-
 	if (pathspec->nr)
 		ps_matched = xcalloc(pathspec->nr, 1);
 
 	if (read_cache() < 0)
 		die(_("index file corrupt"));
 
 	for (i = 0; i < active_nr; i++) {
 		const struct cache_entry *ce = active_cache[i];
 
 		if (!S_ISGITLINK(ce->ce_mode) ||
 		    !match_pathspec(pathspec, ce->name, ce_namelen(ce),
-				    max_prefix_len, ps_matched, 1))
+				    0, ps_matched, 1))
 			continue;
 
 		ALLOC_GROW(list->entries, list->nr + 1, list->alloc);
 		list->entries[list->nr++] = ce;
 		while (i + 1 < active_nr &&
 		       !strcmp(ce->name, active_cache[i + 1]->name))
 			/*
 			 * Skip entries with the same name in different stages
 			 * to make sure an entry is returned only once.
 			 */
 			i++;
 	}
-	free(max_prefix);
 
 	if (ps_matched && report_path_error(ps_matched, pathspec, prefix))
 		result = -1;
 
 	free(ps_matched);
 
