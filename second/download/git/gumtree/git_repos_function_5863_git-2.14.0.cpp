static int run_sequencer(int argc, const char **argv, struct replay_opts *opts)
{
	const char * const * usage_str = revert_or_cherry_pick_usage(opts);
	const char *me = action_name(opts);
	int cmd = 0;
	struct option base_options[] = {
		OPT_CMDMODE(0, "quit", &cmd, N_("end revert or cherry-pick sequence"), 'q'),
		OPT_CMDMODE(0, "continue", &cmd, N_("resume revert or cherry-pick sequence"), 'c'),
		OPT_CMDMODE(0, "abort", &cmd, N_("cancel revert or cherry-pick sequence"), 'a'),
		OPT_BOOL('n', "no-commit", &opts->no_commit, N_("don't automatically commit")),
		OPT_BOOL('e', "edit", &opts->edit, N_("edit the commit message")),
		OPT_NOOP_NOARG('r', NULL),
		OPT_BOOL('s', "signoff", &opts->signoff, N_("add Signed-off-by:")),
		OPT_CALLBACK('m', "mainline", opts, N_("parent-number"),
			     N_("select mainline parent"), option_parse_m),
		OPT_RERERE_AUTOUPDATE(&opts->allow_rerere_auto),
		OPT_STRING(0, "strategy", &opts->strategy, N_("strategy"), N_("merge strategy")),
		OPT_CALLBACK('X', "strategy-option", &opts, N_("option"),
			N_("option for merge strategy"), option_parse_x),
		{ OPTION_STRING, 'S', "gpg-sign", &opts->gpg_sign, N_("key-id"),
		  N_("GPG sign commit"), PARSE_OPT_OPTARG, NULL, (intptr_t) "" },
		OPT_END()
	};
	struct option *options = base_options;

	if (opts->action == REPLAY_PICK) {
		struct option cp_extra[] = {
			OPT_BOOL('x', NULL, &opts->record_origin, N_("append commit name")),
			OPT_BOOL(0, "ff", &opts->allow_ff, N_("allow fast-forward")),
			OPT_BOOL(0, "allow-empty", &opts->allow_empty, N_("preserve initially empty commits")),
			OPT_BOOL(0, "allow-empty-message", &opts->allow_empty_message, N_("allow commits with empty messages")),
			OPT_BOOL(0, "keep-redundant-commits", &opts->keep_redundant_commits, N_("keep redundant, empty commits")),
			OPT_END(),
		};
		options = parse_options_concat(options, cp_extra);
	}

	argc = parse_options(argc, argv, NULL, options, usage_str,
			PARSE_OPT_KEEP_ARGV0 |
			PARSE_OPT_KEEP_UNKNOWN);

	/* implies allow_empty */
	if (opts->keep_redundant_commits)
		opts->allow_empty = 1;

	/* Check for incompatible command line arguments */
	if (cmd) {
		char *this_operation;
		if (cmd == 'q')
			this_operation = "--quit";
		else if (cmd == 'c')
			this_operation = "--continue";
		else {
			assert(cmd == 'a');
			this_operation = "--abort";
		}

		verify_opt_compatible(me, this_operation,
				"--no-commit", opts->no_commit,
				"--signoff", opts->signoff,
				"--mainline", opts->mainline,
				"--strategy", opts->strategy ? 1 : 0,
				"--strategy-option", opts->xopts ? 1 : 0,
				"-x", opts->record_origin,
				"--ff", opts->allow_ff,
				NULL);
	}

	if (opts->allow_ff)
		verify_opt_compatible(me, "--ff",
				"--signoff", opts->signoff,
				"--no-commit", opts->no_commit,
				"-x", opts->record_origin,
				"--edit", opts->edit,
				NULL);

	if (cmd) {
		opts->revs = NULL;
	} else {
		struct setup_revision_opt s_r_opt;
		opts->revs = xmalloc(sizeof(*opts->revs));
		init_revisions(opts->revs, NULL);
		opts->revs->no_walk = REVISION_WALK_NO_WALK_UNSORTED;
		if (argc < 2)
			usage_with_options(usage_str, options);
		if (!strcmp(argv[1], "-"))
			argv[1] = "@{-1}";
		memset(&s_r_opt, 0, sizeof(s_r_opt));
		s_r_opt.assume_dashdash = 1;
		argc = setup_revisions(argc, argv, opts->revs, &s_r_opt);
	}

	if (argc > 1)
		usage_with_options(usage_str, options);

	/* These option values will be free()d */
	opts->gpg_sign = xstrdup_or_null(opts->gpg_sign);
	opts->strategy = xstrdup_or_null(opts->strategy);

	if (cmd == 'q')
		return sequencer_remove_state(opts);
	if (cmd == 'c')
		return sequencer_continue(opts);
	if (cmd == 'a')
		return sequencer_rollback(opts);
	return sequencer_pick_revisions(opts);
}