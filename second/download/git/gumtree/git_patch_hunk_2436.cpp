 	if (read_cache_preload(&opts->pathspec) < 0)
 		return error(_("corrupt index file"));
 
 	if (opts->source_tree)
 		read_tree_some(opts->source_tree, &opts->pathspec);
 
-	ps_matched = xcalloc(1, opts->pathspec.nr);
+	ps_matched = xcalloc(opts->pathspec.nr, 1);
 
 	/*
 	 * Make sure all pathspecs participated in locating the paths
 	 * to be checked out.
 	 */
 	for (pos = 0; pos < active_nr; pos++) {
