 		 * be shared with the_index.cache[]. So yeah we're
 		 * leaking a bit here.
 		 */
 		the_index.split_index = NULL;
 		the_index.cache_changed |= SOMETHING_CHANGED;
 	}
-	if (untracked_cache > 0) {
-		struct untracked_cache *uc;
 
-		if (untracked_cache < 2) {
-			setup_work_tree();
-			if (!test_if_untracked_cache_is_supported())
-				return 1;
-		}
-		if (!the_index.untracked) {
-			uc = xcalloc(1, sizeof(*uc));
-			strbuf_init(&uc->ident, 100);
-			uc->exclude_per_dir = ".gitignore";
-			/* should be the same flags used by git-status */
-			uc->dir_flags = DIR_SHOW_OTHER_DIRECTORIES | DIR_HIDE_EMPTY_DIRECTORIES;
-			the_index.untracked = uc;
-		}
-		add_untracked_ident(the_index.untracked);
-		the_index.cache_changed |= UNTRACKED_CHANGED;
-	} else if (!untracked_cache && the_index.untracked) {
-		the_index.untracked = NULL;
-		the_index.cache_changed |= UNTRACKED_CHANGED;
+	switch (untracked_cache) {
+	case UC_UNSPECIFIED:
+		break;
+	case UC_DISABLE:
+		if (git_config_get_untracked_cache() == 1)
+			warning("core.untrackedCache is set to true; "
+				"remove or change it, if you really want to "
+				"disable the untracked cache");
+		remove_untracked_cache(&the_index);
+		report(_("Untracked cache disabled"));
+		break;
+	case UC_TEST:
+		setup_work_tree();
+		return !test_if_untracked_cache_is_supported();
+	case UC_ENABLE:
+	case UC_FORCE:
+		if (git_config_get_untracked_cache() == 0)
+			warning("core.untrackedCache is set to false; "
+				"remove or change it, if you really want to "
+				"enable the untracked cache");
+		add_untracked_cache(&the_index);
+		report(_("Untracked cache enabled for '%s'"), get_git_work_tree());
+		break;
+	default:
+		die("Bug: bad untracked_cache value: %d", untracked_cache);
 	}
 
 	if (active_cache_changed) {
 		if (newfd < 0) {
 			if (refresh_args.flags & REFRESH_QUIET)
 				exit(128);
