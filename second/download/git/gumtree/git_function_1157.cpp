int cmd_checkout(int argc, const char **argv, const char *prefix)
{
	struct checkout_opts opts;
	struct branch_info new;
	char *conflict_style = NULL;
	int dwim_new_local_branch = 1;
	struct option options[] = {
		OPT__QUIET(&opts.quiet, N_("suppress progress reporting")),
		OPT_STRING('b', NULL, &opts.new_branch, N_("branch"),
			   N_("create and checkout a new branch")),
		OPT_STRING('B', NULL, &opts.new_branch_force, N_("branch"),
			   N_("create/reset and checkout a branch")),
		OPT_BOOL('l', NULL, &opts.new_branch_log, N_("create reflog for new branch")),
		OPT_BOOL(0, "detach", &opts.force_detach, N_("detach HEAD at named commit")),
		OPT_SET_INT('t', "track",  &opts.track, N_("set upstream info for new branch"),
			BRANCH_TRACK_EXPLICIT),
		OPT_STRING(0, "orphan", &opts.new_orphan_branch, N_("new-branch"), N_("new unparented branch")),
		OPT_SET_INT('2', "ours", &opts.writeout_stage, N_("checkout our version for unmerged files"),
			    2),
		OPT_SET_INT('3', "theirs", &opts.writeout_stage, N_("checkout their version for unmerged files"),
			    3),
		OPT__FORCE(&opts.force, N_("force checkout (throw away local modifications)")),
		OPT_BOOL('m', "merge", &opts.merge, N_("perform a 3-way merge with the new branch")),
		OPT_BOOL(0, "overwrite-ignore", &opts.overwrite_ignore, N_("update ignored files (default)")),
		OPT_STRING(0, "conflict", &conflict_style, N_("style"),
			   N_("conflict style (merge or diff3)")),
		OPT_BOOL('p', "patch", &opts.patch_mode, N_("select hunks interactively")),
		OPT_BOOL(0, "ignore-skip-worktree-bits", &opts.ignore_skipworktree,
			 N_("do not limit pathspecs to sparse entries only")),
		OPT_HIDDEN_BOOL(0, "guess", &dwim_new_local_branch,
				N_("second guess 'git checkout <no-such-branch>'")),
		OPT_BOOL(0, "ignore-other-worktrees", &opts.ignore_other_worktrees,
			 N_("do not check if another worktree is holding the given ref")),
		{ OPTION_CALLBACK, 0, "recurse-submodules", &recurse_submodules,
			    "checkout", "control recursive updating of submodules",
			    PARSE_OPT_OPTARG, option_parse_recurse_submodules },
		OPT_BOOL(0, "progress", &opts.show_progress, N_("force progress reporting")),
		OPT_END(),
	};

	memset(&opts, 0, sizeof(opts));
	memset(&new, 0, sizeof(new));
	opts.overwrite_ignore = 1;
	opts.prefix = prefix;
	opts.show_progress = -1;

	gitmodules_config();
	git_config(git_checkout_config, &opts);

	opts.track = BRANCH_TRACK_UNSPECIFIED;

	argc = parse_options(argc, argv, prefix, options, checkout_usage,
			     PARSE_OPT_KEEP_DASHDASH);

	if (opts.show_progress < 0) {
		if (opts.quiet)
			opts.show_progress = 0;
		else
			opts.show_progress = isatty(2);
	}

	if (conflict_style) {
		opts.merge = 1; /* implied */
		git_xmerge_config("merge.conflictstyle", conflict_style, NULL);
	}

	if (recurse_submodules != RECURSE_SUBMODULES_OFF) {
		git_config(submodule_config, NULL);
		if (recurse_submodules != RECURSE_SUBMODULES_DEFAULT)
			set_config_update_recurse_submodules(recurse_submodules);
	}

	if ((!!opts.new_branch + !!opts.new_branch_force + !!opts.new_orphan_branch) > 1)
		die(_("-b, -B and --orphan are mutually exclusive"));

	/*
	 * From here on, new_branch will contain the branch to be checked out,
	 * and new_branch_force and new_orphan_branch will tell us which one of
	 * -b/-B/--orphan is being used.
	 */
	if (opts.new_branch_force)
		opts.new_branch = opts.new_branch_force;

	if (opts.new_orphan_branch)
		opts.new_branch = opts.new_orphan_branch;

	/* --track without -b/-B/--orphan should DWIM */
	if (opts.track != BRANCH_TRACK_UNSPECIFIED && !opts.new_branch) {
		const char *argv0 = argv[0];
		if (!argc || !strcmp(argv0, "--"))
			die (_("--track needs a branch name"));
		skip_prefix(argv0, "refs/", &argv0);
		skip_prefix(argv0, "remotes/", &argv0);
		argv0 = strchr(argv0, '/');
		if (!argv0 || !argv0[1])
			die (_("Missing branch name; try -b"));
		opts.new_branch = argv0 + 1;
	}

	/*
	 * Extract branch name from command line arguments, so
	 * all that is left is pathspecs.
	 *
	 * Handle
	 *
	 *  1) git checkout <tree> -- [<paths>]
	 *  2) git checkout -- [<paths>]
	 *  3) git checkout <something> [<paths>]
	 *
	 * including "last branch" syntax and DWIM-ery for names of
	 * remote branches, erroring out for invalid or ambiguous cases.
	 */
	if (argc) {
		struct object_id rev;
		int dwim_ok =
			!opts.patch_mode &&
			dwim_new_local_branch &&
			opts.track == BRANCH_TRACK_UNSPECIFIED &&
			!opts.new_branch;
		int n = parse_branchname_arg(argc, argv, dwim_ok,
					     &new, &opts, &rev);
		argv += n;
		argc -= n;
	}

	if (argc) {
		parse_pathspec(&opts.pathspec, 0,
			       opts.patch_mode ? PATHSPEC_PREFIX_ORIGIN : 0,
			       prefix, argv);

		if (!opts.pathspec.nr)
			die(_("invalid path specification"));

		/*
		 * Try to give more helpful suggestion.
		 * new_branch && argc > 1 will be caught later.
		 */
		if (opts.new_branch && argc == 1)
			die(_("Cannot update paths and switch to branch '%s' at the same time.\n"
			      "Did you intend to checkout '%s' which can not be resolved as commit?"),
			    opts.new_branch, argv[0]);

		if (opts.force_detach)
			die(_("git checkout: --detach does not take a path argument '%s'"),
			    argv[0]);

		if (1 < !!opts.writeout_stage + !!opts.force + !!opts.merge)
			die(_("git checkout: --ours/--theirs, --force and --merge are incompatible when\n"
			      "checking out of the index."));
	}

	if (opts.new_branch) {
		struct strbuf buf = STRBUF_INIT;

		opts.branch_exists =
			validate_new_branchname(opts.new_branch, &buf,
						!!opts.new_branch_force,
						!!opts.new_branch_force);

		strbuf_release(&buf);
	}

	if (opts.patch_mode || opts.pathspec.nr)
		return checkout_paths(&opts, new.name);
	else
		return checkout_branch(&opts, &new);
}