 
 	git_config(git_pull_config, NULL);
 
 	if (read_cache_unmerged())
 		die_resolve_conflict("pull");
 
-	if (file_exists(git_path("MERGE_HEAD")))
+	if (file_exists(git_path_merge_head()))
 		die_conclude_merge();
 
-	if (get_sha1("HEAD", orig_head))
-		hashclr(orig_head);
+	if (get_oid("HEAD", &orig_head))
+		oidclr(&orig_head);
 
 	if (!opt_rebase && opt_autostash != -1)
 		die(_("--[no-]autostash option is only valid with --rebase."));
 
 	if (opt_rebase) {
 		int autostash = config_autostash;
 		if (opt_autostash != -1)
 			autostash = opt_autostash;
 
-		if (is_null_sha1(orig_head) && !is_cache_unborn())
+		if (is_null_oid(&orig_head) && !is_cache_unborn())
 			die(_("Updating an unborn branch with changes added to the index."));
 
 		if (!autostash)
 			require_clean_work_tree(N_("pull with rebase"),
 				_("please commit or stash them."), 1, 0);
 
-		if (get_rebase_fork_point(rebase_fork_point, repo, *refspecs))
-			hashclr(rebase_fork_point);
+		if (get_rebase_fork_point(&rebase_fork_point, repo, *refspecs))
+			oidclr(&rebase_fork_point);
 	}
 
 	if (run_fetch(repo, refspecs))
 		return 1;
 
 	if (opt_dry_run)
 		return 0;
 
-	if (get_sha1("HEAD", curr_head))
-		hashclr(curr_head);
+	if (get_oid("HEAD", &curr_head))
+		oidclr(&curr_head);
 
-	if (!is_null_sha1(orig_head) && !is_null_sha1(curr_head) &&
-			hashcmp(orig_head, curr_head)) {
+	if (!is_null_oid(&orig_head) && !is_null_oid(&curr_head) &&
+			oidcmp(&orig_head, &curr_head)) {
 		/*
 		 * The fetch involved updating the current branch.
 		 *
 		 * The working tree and the index file are still based on
 		 * orig_head commit, but we are merging into curr_head.
 		 * Update the working tree to match curr_head.
 		 */
 
 		warning(_("fetch updated the current branch head.\n"
 			"fast-forwarding your working tree from\n"
-			"commit %s."), sha1_to_hex(orig_head));
+			"commit %s."), oid_to_hex(&orig_head));
 
-		if (checkout_fast_forward(orig_head, curr_head, 0))
+		if (checkout_fast_forward(orig_head.hash, curr_head.hash, 0))
 			die(_("Cannot fast-forward your working tree.\n"
 				"After making sure that you saved anything precious from\n"
 				"$ git diff %s\n"
 				"output, run\n"
 				"$ git reset --hard\n"
-				"to recover."), sha1_to_hex(orig_head));
+				"to recover."), oid_to_hex(&orig_head));
 	}
 
 	get_merge_heads(&merge_heads);
 
 	if (!merge_heads.nr)
 		die_no_merge_candidates(repo, refspecs);
 
-	if (is_null_sha1(orig_head)) {
+	if (is_null_oid(&orig_head)) {
 		if (merge_heads.nr > 1)
 			die(_("Cannot merge multiple branches into empty head."));
-		return pull_into_void(*merge_heads.sha1, curr_head);
+		return pull_into_void(merge_heads.oid, &curr_head);
 	}
 	if (opt_rebase && merge_heads.nr > 1)
 		die(_("Cannot rebase onto multiple branches."));
 
 	if (opt_rebase) {
 		struct commit_list *list = NULL;
 		struct commit *merge_head, *head;
 
-		head = lookup_commit_reference(orig_head);
+		head = lookup_commit_reference(orig_head.hash);
 		commit_list_insert(head, &list);
-		merge_head = lookup_commit_reference(merge_heads.sha1[0]);
+		merge_head = lookup_commit_reference(merge_heads.oid[0].hash);
 		if (is_descendant_of(merge_head, list)) {
 			/* we can fast-forward this without invoking rebase */
 			opt_ff = "--ff-only";
 			return run_merge();
 		}
-		return run_rebase(curr_head, *merge_heads.sha1, rebase_fork_point);
+		return run_rebase(&curr_head, merge_heads.oid, &rebase_fork_point);
 	} else {
 		return run_merge();
 	}
 }
