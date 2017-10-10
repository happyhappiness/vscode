 	if (!opt_ff)
 		opt_ff = xstrdup_or_null(config_get_ff());
 
 	if (opt_rebase < 0)
 		opt_rebase = config_get_rebase();
 
-	git_config(git_default_config, NULL);
+	git_config(git_pull_config, NULL);
 
 	if (read_cache_unmerged())
 		die_resolve_conflict("Pull");
 
 	if (file_exists(git_path("MERGE_HEAD")))
 		die_conclude_merge();
 
 	if (get_sha1("HEAD", orig_head))
 		hashclr(orig_head);
 
+	if (!opt_rebase && opt_autostash != -1)
+		die(_("--[no-]autostash option is only valid with --rebase."));
+
 	if (opt_rebase) {
-		int autostash = 0;
+		int autostash = config_autostash;
+		if (opt_autostash != -1)
+			autostash = opt_autostash;
 
 		if (is_null_sha1(orig_head) && !is_cache_unborn())
 			die(_("Updating an unborn branch with changes added to the index."));
 
-		git_config_get_bool("rebase.autostash", &autostash);
 		if (!autostash)
 			die_on_unclean_work_tree(prefix);
 
 		if (get_rebase_fork_point(rebase_fork_point, repo, *refspecs))
 			hashclr(rebase_fork_point);
 	}
