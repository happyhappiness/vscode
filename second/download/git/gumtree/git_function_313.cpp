int cmd_update_index(int argc, const char **argv, const char *prefix)
{
	int newfd, entries, has_errors = 0, nul_term_line = 0;
	enum uc_mode untracked_cache = UC_UNSPECIFIED;
	int read_from_stdin = 0;
	int prefix_length = prefix ? strlen(prefix) : 0;
	int preferred_index_format = 0;
	char set_executable_bit = 0;
	struct refresh_params refresh_args = {0, &has_errors};
	int lock_error = 0;
	int split_index = -1;
	struct lock_file *lock_file;
	struct parse_opt_ctx_t ctx;
	strbuf_getline_fn getline_fn;
	int parseopt_state = PARSE_OPT_UNKNOWN;
	struct option options[] = {
		OPT_BIT('q', NULL, &refresh_args.flags,
			N_("continue refresh even when index needs update"),
			REFRESH_QUIET),
		OPT_BIT(0, "ignore-submodules", &refresh_args.flags,
			N_("refresh: ignore submodules"),
			REFRESH_IGNORE_SUBMODULES),
		OPT_SET_INT(0, "add", &allow_add,
			N_("do not ignore new files"), 1),
		OPT_SET_INT(0, "replace", &allow_replace,
			N_("let files replace directories and vice-versa"), 1),
		OPT_SET_INT(0, "remove", &allow_remove,
			N_("notice files missing from worktree"), 1),
		OPT_BIT(0, "unmerged", &refresh_args.flags,
			N_("refresh even if index contains unmerged entries"),
			REFRESH_UNMERGED),
		{OPTION_CALLBACK, 0, "refresh", &refresh_args, NULL,
			N_("refresh stat information"),
			PARSE_OPT_NOARG | PARSE_OPT_NONEG,
			refresh_callback},
		{OPTION_CALLBACK, 0, "really-refresh", &refresh_args, NULL,
			N_("like --refresh, but ignore assume-unchanged setting"),
			PARSE_OPT_NOARG | PARSE_OPT_NONEG,
			really_refresh_callback},
		{OPTION_LOWLEVEL_CALLBACK, 0, "cacheinfo", NULL,
			N_("<mode>,<object>,<path>"),
			N_("add the specified entry to the index"),
			PARSE_OPT_NOARG | /* disallow --cacheinfo=<mode> form */
			PARSE_OPT_NONEG | PARSE_OPT_LITERAL_ARGHELP,
			(parse_opt_cb *) cacheinfo_callback},
		{OPTION_CALLBACK, 0, "chmod", &set_executable_bit, N_("(+/-)x"),
			N_("override the executable bit of the listed files"),
			PARSE_OPT_NONEG | PARSE_OPT_LITERAL_ARGHELP,
			chmod_callback},
		{OPTION_SET_INT, 0, "assume-unchanged", &mark_valid_only, NULL,
			N_("mark files as \"not changing\""),
			PARSE_OPT_NOARG | PARSE_OPT_NONEG, NULL, MARK_FLAG},
		{OPTION_SET_INT, 0, "no-assume-unchanged", &mark_valid_only, NULL,
			N_("clear assumed-unchanged bit"),
			PARSE_OPT_NOARG | PARSE_OPT_NONEG, NULL, UNMARK_FLAG},
		{OPTION_SET_INT, 0, "skip-worktree", &mark_skip_worktree_only, NULL,
			N_("mark files as \"index-only\""),
			PARSE_OPT_NOARG | PARSE_OPT_NONEG, NULL, MARK_FLAG},
		{OPTION_SET_INT, 0, "no-skip-worktree", &mark_skip_worktree_only, NULL,
			N_("clear skip-worktree bit"),
			PARSE_OPT_NOARG | PARSE_OPT_NONEG, NULL, UNMARK_FLAG},
		OPT_SET_INT(0, "info-only", &info_only,
			N_("add to index only; do not add content to object database"), 1),
		OPT_SET_INT(0, "force-remove", &force_remove,
			N_("remove named paths even if present in worktree"), 1),
		OPT_BOOL('z', NULL, &nul_term_line,
			 N_("with --stdin: input lines are terminated by null bytes")),
		{OPTION_LOWLEVEL_CALLBACK, 0, "stdin", &read_from_stdin, NULL,
			N_("read list of paths to be updated from standard input"),
			PARSE_OPT_NONEG | PARSE_OPT_NOARG,
			(parse_opt_cb *) stdin_callback},
		{OPTION_LOWLEVEL_CALLBACK, 0, "index-info", &nul_term_line, NULL,
			N_("add entries from standard input to the index"),
			PARSE_OPT_NONEG | PARSE_OPT_NOARG,
			(parse_opt_cb *) stdin_cacheinfo_callback},
		{OPTION_LOWLEVEL_CALLBACK, 0, "unresolve", &has_errors, NULL,
			N_("repopulate stages #2 and #3 for the listed paths"),
			PARSE_OPT_NONEG | PARSE_OPT_NOARG,
			(parse_opt_cb *) unresolve_callback},
		{OPTION_LOWLEVEL_CALLBACK, 'g', "again", &has_errors, NULL,
			N_("only update entries that differ from HEAD"),
			PARSE_OPT_NONEG | PARSE_OPT_NOARG,
			(parse_opt_cb *) reupdate_callback},
		OPT_BIT(0, "ignore-missing", &refresh_args.flags,
			N_("ignore files missing from worktree"),
			REFRESH_IGNORE_MISSING),
		OPT_SET_INT(0, "verbose", &verbose,
			N_("report actions to standard output"), 1),
		{OPTION_CALLBACK, 0, "clear-resolve-undo", NULL, NULL,
			N_("(for porcelains) forget saved unresolved conflicts"),
			PARSE_OPT_NOARG | PARSE_OPT_NONEG,
			resolve_undo_clear_callback},
		OPT_INTEGER(0, "index-version", &preferred_index_format,
			N_("write index in this format")),
		OPT_BOOL(0, "split-index", &split_index,
			N_("enable or disable split index")),
		OPT_BOOL(0, "untracked-cache", &untracked_cache,
			N_("enable/disable untracked cache")),
		OPT_SET_INT(0, "test-untracked-cache", &untracked_cache,
			    N_("test if the filesystem supports untracked cache"), UC_TEST),
		OPT_SET_INT(0, "force-untracked-cache", &untracked_cache,
			    N_("enable untracked cache without testing the filesystem"), UC_FORCE),
		OPT_END()
	};

	if (argc == 2 && !strcmp(argv[1], "-h"))
		usage_with_options(update_index_usage, options);

	git_config(git_default_config, NULL);

	/* We can't free this memory, it becomes part of a linked list parsed atexit() */
	lock_file = xcalloc(1, sizeof(struct lock_file));

	newfd = hold_locked_index(lock_file, 0);
	if (newfd < 0)
		lock_error = errno;

	entries = read_cache();
	if (entries < 0)
		die("cache corrupted");

	/*
	 * Custom copy of parse_options() because we want to handle
	 * filename arguments as they come.
	 */
	parse_options_start(&ctx, argc, argv, prefix,
			    options, PARSE_OPT_STOP_AT_NON_OPTION);
	while (ctx.argc) {
		if (parseopt_state != PARSE_OPT_DONE)
			parseopt_state = parse_options_step(&ctx, options,
							    update_index_usage);
		if (!ctx.argc)
			break;
		switch (parseopt_state) {
		case PARSE_OPT_HELP:
			exit(129);
		case PARSE_OPT_NON_OPTION:
		case PARSE_OPT_DONE:
		{
			const char *path = ctx.argv[0];
			char *p;

			setup_work_tree();
			p = prefix_path(prefix, prefix_length, path);
			update_one(p);
			if (set_executable_bit)
				chmod_path(set_executable_bit, p);
			free(p);
			ctx.argc--;
			ctx.argv++;
			break;
		}
		case PARSE_OPT_UNKNOWN:
			if (ctx.argv[0][1] == '-')
				error("unknown option '%s'", ctx.argv[0] + 2);
			else
				error("unknown switch '%c'", *ctx.opt);
			usage_with_options(update_index_usage, options);
		}
	}
	argc = parse_options_end(&ctx);

	getline_fn = nul_term_line ? strbuf_getline_nul : strbuf_getline_lf;
	if (preferred_index_format) {
		if (preferred_index_format < INDEX_FORMAT_LB ||
		    INDEX_FORMAT_UB < preferred_index_format)
			die("index-version %d not in range: %d..%d",
			    preferred_index_format,
			    INDEX_FORMAT_LB, INDEX_FORMAT_UB);

		if (the_index.version != preferred_index_format)
			active_cache_changed |= SOMETHING_CHANGED;
		the_index.version = preferred_index_format;
	}

	if (read_from_stdin) {
		struct strbuf buf = STRBUF_INIT;
		struct strbuf unquoted = STRBUF_INIT;

		setup_work_tree();
		while (getline_fn(&buf, stdin) != EOF) {
			char *p;
			if (!nul_term_line && buf.buf[0] == '"') {
				strbuf_reset(&unquoted);
				if (unquote_c_style(&unquoted, buf.buf, NULL))
					die("line is badly quoted");
				strbuf_swap(&buf, &unquoted);
			}
			p = prefix_path(prefix, prefix_length, buf.buf);
			update_one(p);
			if (set_executable_bit)
				chmod_path(set_executable_bit, p);
			free(p);
		}
		strbuf_release(&unquoted);
		strbuf_release(&buf);
	}

	if (split_index > 0) {
		init_split_index(&the_index);
		the_index.cache_changed |= SPLIT_INDEX_ORDERED;
	} else if (!split_index && the_index.split_index) {
		/*
		 * can't discard_split_index(&the_index); because that
		 * will destroy split_index->base->cache[], which may
		 * be shared with the_index.cache[]. So yeah we're
		 * leaking a bit here.
		 */
		the_index.split_index = NULL;
		the_index.cache_changed |= SOMETHING_CHANGED;
	}

	switch (untracked_cache) {
	case UC_UNSPECIFIED:
		break;
	case UC_DISABLE:
		if (git_config_get_untracked_cache() == 1)
			warning("core.untrackedCache is set to true; "
				"remove or change it, if you really want to "
				"disable the untracked cache");
		remove_untracked_cache(&the_index);
		report(_("Untracked cache disabled"));
		break;
	case UC_TEST:
		setup_work_tree();
		return !test_if_untracked_cache_is_supported();
	case UC_ENABLE:
	case UC_FORCE:
		if (git_config_get_untracked_cache() == 0)
			warning("core.untrackedCache is set to false; "
				"remove or change it, if you really want to "
				"enable the untracked cache");
		add_untracked_cache(&the_index);
		report(_("Untracked cache enabled for '%s'"), get_git_work_tree());
		break;
	default:
		die("BUG: bad untracked_cache value: %d", untracked_cache);
	}

	if (active_cache_changed) {
		if (newfd < 0) {
			if (refresh_args.flags & REFRESH_QUIET)
				exit(128);
			unable_to_lock_die(get_index_file(), lock_error);
		}
		if (write_locked_index(&the_index, lock_file, COMMIT_LOCK))
			die("Unable to write new index file");
	}

	rollback_lock_file(lock_file);

	return has_errors ? 1 : 0;
}