 		if (quiet)
 			argv_array_push(&prune, "--no-progress");
 		if (run_command_v_opt(prune.argv, RUN_GIT_CMD))
 			return error(FAILED_RUN, prune.argv[0]);
 	}
 
+	if (prune_worktrees_expire) {
+		argv_array_push(&prune_worktrees, prune_worktrees_expire);
+		if (run_command_v_opt(prune_worktrees.argv, RUN_GIT_CMD))
+			return error(FAILED_RUN, prune_worktrees.argv[0]);
+	}
+
 	if (run_command_v_opt(rerere.argv, RUN_GIT_CMD))
 		return error(FAILED_RUN, rerere.argv[0]);
 
 	if (auto_gc && too_many_loose_objects())
 		warning(_("There are too many unreachable loose objects; "
 			"run 'git prune' to remove them."));
