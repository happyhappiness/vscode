 				"remove or change it, if you really want to "
 				"enable the untracked cache");
 		add_untracked_cache(&the_index);
 		report(_("Untracked cache enabled for '%s'"), get_git_work_tree());
 		break;
 	default:
-		die("Bug: bad untracked_cache value: %d", untracked_cache);
+		die("BUG: bad untracked_cache value: %d", untracked_cache);
 	}
 
 	if (active_cache_changed) {
 		if (newfd < 0) {
 			if (refresh_args.flags & REFRESH_QUIET)
 				exit(128);
