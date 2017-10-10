 			autostash = opt_autostash;
 
 		if (is_null_sha1(orig_head) && !is_cache_unborn())
 			die(_("Updating an unborn branch with changes added to the index."));
 
 		if (!autostash)
-			die_on_unclean_work_tree(prefix);
+			require_clean_work_tree(N_("pull with rebase"),
+				_("please commit or stash them."), 1, 0);
 
 		if (get_rebase_fork_point(rebase_fork_point, repo, *refspecs))
 			hashclr(rebase_fork_point);
 	}
 
 	if (run_fetch(repo, refspecs))
