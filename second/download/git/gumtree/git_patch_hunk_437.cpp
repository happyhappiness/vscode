 
 	switch (untracked_cache) {
 	case UC_UNSPECIFIED:
 		break;
 	case UC_DISABLE:
 		if (git_config_get_untracked_cache() == 1)
-			warning("core.untrackedCache is set to true; "
-				"remove or change it, if you really want to "
-				"disable the untracked cache");
+			warning(_("core.untrackedCache is set to true; "
+				  "remove or change it, if you really want to "
+				  "disable the untracked cache"));
 		remove_untracked_cache(&the_index);
 		report(_("Untracked cache disabled"));
 		break;
 	case UC_TEST:
 		setup_work_tree();
 		return !test_if_untracked_cache_is_supported();
 	case UC_ENABLE:
 	case UC_FORCE:
 		if (git_config_get_untracked_cache() == 0)
-			warning("core.untrackedCache is set to false; "
-				"remove or change it, if you really want to "
-				"enable the untracked cache");
+			warning(_("core.untrackedCache is set to false; "
+				  "remove or change it, if you really want to "
+				  "enable the untracked cache"));
 		add_untracked_cache(&the_index);
 		report(_("Untracked cache enabled for '%s'"), get_git_work_tree());
 		break;
 	default:
 		die("BUG: bad untracked_cache value: %d", untracked_cache);
 	}
