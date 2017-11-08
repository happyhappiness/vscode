int cmd_gc(int argc, const char **argv, const char *prefix)
{
	int aggressive = 0;
	int auto_gc = 0;
	int quiet = 0;
	int force = 0;
	const char *name;
	pid_t pid;
	int daemonized = 0;

	struct option builtin_gc_options[] = {
		OPT__QUIET(&quiet, N_("suppress progress reporting")),
		{ OPTION_STRING, 0, "prune", &prune_expire, N_("date"),
			N_("prune unreferenced objects"),
			PARSE_OPT_OPTARG, NULL, (intptr_t)prune_expire },
		OPT_BOOL(0, "aggressive", &aggressive, N_("be more thorough (increased runtime)")),
		OPT_BOOL(0, "auto", &auto_gc, N_("enable auto-gc mode")),
		OPT_BOOL(0, "force", &force, N_("force running gc even if there may be another gc running")),
		OPT_END()
	};

	if (argc == 2 && !strcmp(argv[1], "-h"))
		usage_with_options(builtin_gc_usage, builtin_gc_options);

	argv_array_pushl(&pack_refs_cmd, "pack-refs", "--all", "--prune", NULL);
	argv_array_pushl(&reflog, "reflog", "expire", "--all", NULL);
	argv_array_pushl(&repack, "repack", "-d", "-l", NULL);
	argv_array_pushl(&prune, "prune", "--expire", NULL);
	argv_array_pushl(&prune_worktrees, "worktree", "prune", "--expire", NULL);
	argv_array_pushl(&rerere, "rerere", "gc", NULL);

	/* default expiry time, overwritten in gc_config */
	gc_config();
	if (parse_expiry_date(gc_log_expire, &gc_log_expire_time))
		die(_("Failed to parse gc.logexpiry value %s"), gc_log_expire);

	if (pack_refs < 0)
		pack_refs = !is_bare_repository();

	argc = parse_options(argc, argv, prefix, builtin_gc_options,
			     builtin_gc_usage, 0);
	if (argc > 0)
		usage_with_options(builtin_gc_usage, builtin_gc_options);

	if (aggressive) {
		argv_array_push(&repack, "-f");
		if (aggressive_depth > 0)
			argv_array_pushf(&repack, "--depth=%d", aggressive_depth);
		if (aggressive_window > 0)
			argv_array_pushf(&repack, "--window=%d", aggressive_window);
	}
	if (quiet)
		argv_array_push(&repack, "-q");

	if (auto_gc) {
		/*
		 * Auto-gc should be least intrusive as possible.
		 */
		if (!need_to_gc())
			return 0;
		if (!quiet) {
			if (detach_auto)
				fprintf(stderr, _("Auto packing the repository in background for optimum performance.\n"));
			else
				fprintf(stderr, _("Auto packing the repository for optimum performance.\n"));
			fprintf(stderr, _("See \"git help gc\" for manual housekeeping.\n"));
		}
		if (detach_auto) {
			if (report_last_gc_error())
				return -1;

			if (gc_before_repack())
				return -1;
			/*
			 * failure to daemonize is ok, we'll continue
			 * in foreground
			 */
			daemonized = !daemonize();
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

	if (daemonized) {
		hold_lock_file_for_update(&log_lock,
					  git_path("gc.log"),
					  LOCK_DIE_ON_ERROR);
		dup2(get_lock_file_fd(&log_lock), 2);
		sigchain_push_common(process_log_file_on_signal);
		atexit(process_log_file_at_exit);
	}

	if (gc_before_repack())
		return -1;

	if (!repository_format_precious_objects) {
		if (run_command_v_opt(repack.argv, RUN_GIT_CMD))
			return error(FAILED_RUN, repack.argv[0]);

		if (prune_expire) {
			argv_array_push(&prune, prune_expire);
			if (quiet)
				argv_array_push(&prune, "--no-progress");
			if (run_command_v_opt(prune.argv, RUN_GIT_CMD))
				return error(FAILED_RUN, prune.argv[0]);
		}
	}

	if (prune_worktrees_expire) {
		argv_array_push(&prune_worktrees, prune_worktrees_expire);
		if (run_command_v_opt(prune_worktrees.argv, RUN_GIT_CMD))
			return error(FAILED_RUN, prune_worktrees.argv[0]);
	}

	if (run_command_v_opt(rerere.argv, RUN_GIT_CMD))
		return error(FAILED_RUN, rerere.argv[0]);

	report_garbage = report_pack_garbage;
	reprepare_packed_git();
	if (pack_garbage.nr > 0)
		clean_pack_garbage();

	if (auto_gc && too_many_loose_objects())
		warning(_("There are too many unreachable loose objects; "
			"run 'git prune' to remove them."));

	if (!daemonized)
		unlink(git_path("gc.log"));

	return 0;
}