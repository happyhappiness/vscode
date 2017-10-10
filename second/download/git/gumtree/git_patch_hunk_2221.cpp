 
 	git_config_get_int("gc.aggressivewindow", &aggressive_window);
 	git_config_get_int("gc.aggressivedepth", &aggressive_depth);
 	git_config_get_int("gc.auto", &gc_auto_threshold);
 	git_config_get_int("gc.autopacklimit", &gc_auto_pack_limit);
 	git_config_get_bool("gc.autodetach", &detach_auto);
-
-	if (!git_config_get_string_const("gc.pruneexpire", &prune_expire)) {
-		if (strcmp(prune_expire, "now")) {
-			unsigned long now = approxidate("now");
-			if (approxidate(prune_expire) >= now) {
-				git_die_config("gc.pruneexpire", _("Invalid gc.pruneexpire: '%s'"),
-						prune_expire);
-			}
-		}
-	}
+	git_config_date_string("gc.pruneexpire", &prune_expire);
+	git_config_date_string("gc.pruneworktreesexpire", &prune_worktrees_expire);
 	git_config(git_default_config, NULL);
 }
 
 static int too_many_loose_objects(void)
 {
 	/*
