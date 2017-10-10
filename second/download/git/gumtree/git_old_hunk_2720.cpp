				fprintf(stderr, _("Auto packing the repository in background for optimum performance.\n"));
			else
				fprintf(stderr, _("Auto packing the repository for optimum performance.\n"));
			fprintf(stderr, _("See \"git help gc\" for manual housekeeping.\n"));
		}
		if (detach_auto) {
			if (gc_before_repack())
				return -1;
			/*
			 * failure to daemonize is ok, we'll continue
			 * in foreground
			 */
			daemonize();
		}
	} else
		add_repack_all_option();

	name = lock_repo_for_gc(force, &pid);
	if (name) {
		if (auto_gc)
			return 0; /* be quiet on --auto */
		die(_("gc is already running on machine '%s' pid %"PRIuMAX" (use --force if not)"),
		    name, (uintmax_t)pid);
	}

	if (gc_before_repack())
		return -1;

	if (run_command_v_opt(repack.argv, RUN_GIT_CMD))
		return error(FAILED_RUN, repack.argv[0]);

	if (prune_expire) {
		argv_array_push(&prune, prune_expire);
		if (quiet)
			argv_array_push(&prune, "--no-progress");
		if (run_command_v_opt(prune.argv, RUN_GIT_CMD))
			return error(FAILED_RUN, prune.argv[0]);
	}

	if (prune_worktrees_expire) {
		argv_array_push(&prune_worktrees, prune_worktrees_expire);
		if (run_command_v_opt(prune_worktrees.argv, RUN_GIT_CMD))
			return error(FAILED_RUN, prune_worktrees.argv[0]);
