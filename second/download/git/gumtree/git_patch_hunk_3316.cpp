 			continue;
 		ALLOC_GROW(list.entry, list.nr + 1, list.alloc);
 		list.entry[list.nr].name = xstrdup(ce->name);
 		list.entry[list.nr].is_submodule = S_ISGITLINK(ce->ce_mode);
 		if (list.entry[list.nr++].is_submodule &&
 		    !is_staging_gitmodules_ok())
-			die (_("Please, stage your changes to .gitmodules or stash them to proceed"));
+			die (_("Please stage your changes to .gitmodules or stash them to proceed"));
 	}
 
 	if (pathspec.nr) {
 		const char *original;
 		int seen_any = 0;
 		for (i = 0; i < pathspec.nr; i++) {
