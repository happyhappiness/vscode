 
 	/*
 	 * Pick the result from the best strategy and have the user fix
 	 * it up.
 	 */
 	if (!best_strategy) {
-		restore_state(head_commit->object.sha1, stash);
+		restore_state(head_commit->object.oid.hash, stash);
 		if (use_strategies_nr > 1)
 			fprintf(stderr,
 				_("No merge strategy handled the merge.\n"));
 		else
 			fprintf(stderr, _("Merge with strategy %s failed.\n"),
 				use_strategies[0]->name);
 		ret = 2;
 		goto done;
 	} else if (best_strategy == wt_strategy)
 		; /* We already have its result in the working tree. */
 	else {
 		printf(_("Rewinding the tree to pristine...\n"));
-		restore_state(head_commit->object.sha1, stash);
+		restore_state(head_commit->object.oid.hash, stash);
 		printf(_("Using the %s to prepare resolving by hand.\n"),
 			best_strategy);
 		try_merge_strategy(best_strategy, common, remoteheads,
 				   head_commit, head_arg);
 	}
 
