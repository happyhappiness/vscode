int cmd_am(int argc, const char **argv, const char *prefix)
{
	struct am_state state;
	int binary = -1;
	int keep_cr = -1;
	int patch_format = PATCH_FORMAT_UNKNOWN;
	enum resume_mode resume = RESUME_FALSE;
	int in_progress;

	const char * const usage[] = {
		N_("git am [<options>] [(<mbox> | <Maildir>)...]"),
		N_("git am [<options>] (--continue | --skip | --abort)"),
		NULL
	};

	struct option options[] = {
		OPT_BOOL('i', "interactive", &state.interactive,
			N_("run interactively")),
		OPT_HIDDEN_BOOL('b', "binary", &binary,
			N_("historical option -- no-op")),
		OPT_BOOL('3', "3way", &state.threeway,
			N_("allow fall back on 3way merging if needed")),
		OPT__QUIET(&state.quiet, N_("be quiet")),
		OPT_SET_INT('s', "signoff", &state.signoff,
			N_("add a Signed-off-by line to the commit message"),
			SIGNOFF_EXPLICIT),
		OPT_BOOL('u', "utf8", &state.utf8,
			N_("recode into utf8 (default)")),
		OPT_SET_INT('k', "keep", &state.keep,
			N_("pass -k flag to git-mailinfo"), KEEP_TRUE),
		OPT_SET_INT(0, "keep-non-patch", &state.keep,
			N_("pass -b flag to git-mailinfo"), KEEP_NON_PATCH),
		OPT_BOOL('m', "message-id", &state.message_id,
			N_("pass -m flag to git-mailinfo")),
		{ OPTION_SET_INT, 0, "keep-cr", &keep_cr, NULL,
		  N_("pass --keep-cr flag to git-mailsplit for mbox format"),
		  PARSE_OPT_NOARG | PARSE_OPT_NONEG, NULL, 1},
		{ OPTION_SET_INT, 0, "no-keep-cr", &keep_cr, NULL,
		  N_("do not pass --keep-cr flag to git-mailsplit independent of am.keepcr"),
		  PARSE_OPT_NOARG | PARSE_OPT_NONEG, NULL, 0},
		OPT_BOOL('c', "scissors", &state.scissors,
			N_("strip everything before a scissors line")),
		OPT_PASSTHRU_ARGV(0, "whitespace", &state.git_apply_opts, N_("action"),
			N_("pass it through git-apply"),
			0),
		OPT_PASSTHRU_ARGV(0, "ignore-space-change", &state.git_apply_opts, NULL,
			N_("pass it through git-apply"),
			PARSE_OPT_NOARG),
		OPT_PASSTHRU_ARGV(0, "ignore-whitespace", &state.git_apply_opts, NULL,
			N_("pass it through git-apply"),
			PARSE_OPT_NOARG),
		OPT_PASSTHRU_ARGV(0, "directory", &state.git_apply_opts, N_("root"),
			N_("pass it through git-apply"),
			0),
		OPT_PASSTHRU_ARGV(0, "exclude", &state.git_apply_opts, N_("path"),
			N_("pass it through git-apply"),
			0),
		OPT_PASSTHRU_ARGV(0, "include", &state.git_apply_opts, N_("path"),
			N_("pass it through git-apply"),
			0),
		OPT_PASSTHRU_ARGV('C', NULL, &state.git_apply_opts, N_("n"),
			N_("pass it through git-apply"),
			0),
		OPT_PASSTHRU_ARGV('p', NULL, &state.git_apply_opts, N_("num"),
			N_("pass it through git-apply"),
			0),
		OPT_CALLBACK(0, "patch-format", &patch_format, N_("format"),
			N_("format the patch(es) are in"),
			parse_opt_patchformat),
		OPT_PASSTHRU_ARGV(0, "reject", &state.git_apply_opts, NULL,
			N_("pass it through git-apply"),
			PARSE_OPT_NOARG),
		OPT_STRING(0, "resolvemsg", &state.resolvemsg, NULL,
			N_("override error message when patch failure occurs")),
		OPT_CMDMODE(0, "continue", &resume,
			N_("continue applying patches after resolving a conflict"),
			RESUME_RESOLVED),
		OPT_CMDMODE('r', "resolved", &resume,
			N_("synonyms for --continue"),
			RESUME_RESOLVED),
		OPT_CMDMODE(0, "skip", &resume,
			N_("skip the current patch"),
			RESUME_SKIP),
		OPT_CMDMODE(0, "abort", &resume,
			N_("restore the original branch and abort the patching operation."),
			RESUME_ABORT),
		OPT_BOOL(0, "committer-date-is-author-date",
			&state.committer_date_is_author_date,
			N_("lie about committer date")),
		OPT_BOOL(0, "ignore-date", &state.ignore_date,
			N_("use current timestamp for author date")),
		OPT_RERERE_AUTOUPDATE(&state.allow_rerere_autoupdate),
		{ OPTION_STRING, 'S', "gpg-sign", &state.sign_commit, N_("key-id"),
		  N_("GPG-sign commits"),
		  PARSE_OPT_OPTARG, NULL, (intptr_t) "" },
		OPT_HIDDEN_BOOL(0, "rebasing", &state.rebasing,
			N_("(internal use for git-rebase)")),
		OPT_END()
	};

	if (argc == 2 && !strcmp(argv[1], "-h"))
		usage_with_options(usage, options);

	git_config(git_am_config, NULL);

	am_state_init(&state);

	in_progress = am_in_progress(&state);
	if (in_progress)
		am_load(&state);

	argc = parse_options(argc, argv, prefix, options, usage, 0);

	if (binary >= 0)
		fprintf_ln(stderr, _("The -b/--binary option has been a no-op for long time, and\n"
				"it will be removed. Please do not use it anymore."));

	/* Ensure a valid committer ident can be constructed */
	git_committer_info(IDENT_STRICT);

	if (read_index_preload(&the_index, NULL) < 0)
		die(_("failed to read the index"));

	if (in_progress) {
		/*
		 * Catch user error to feed us patches when there is a session
		 * in progress:
		 *
		 * 1. mbox path(s) are provided on the command-line.
		 * 2. stdin is not a tty: the user is trying to feed us a patch
		 *    from standard input. This is somewhat unreliable -- stdin
		 *    could be /dev/null for example and the caller did not
		 *    intend to feed us a patch but wanted to continue
		 *    unattended.
		 */
		if (argc || (resume == RESUME_FALSE && !isatty(0)))
			die(_("previous rebase directory %s still exists but mbox given."),
				state.dir);

		if (resume == RESUME_FALSE)
			resume = RESUME_APPLY;

		if (state.signoff == SIGNOFF_EXPLICIT)
			am_append_signoff(&state);
	} else {
		struct argv_array paths = ARGV_ARRAY_INIT;
		int i;

		/*
		 * Handle stray state directory in the independent-run case. In
		 * the --rebasing case, it is up to the caller to take care of
		 * stray directories.
		 */
		if (file_exists(state.dir) && !state.rebasing) {
			if (resume == RESUME_ABORT) {
				am_destroy(&state);
				am_state_release(&state);
				return 0;
			}

			die(_("Stray %s directory found.\n"
				"Use \"git am --abort\" to remove it."),
				state.dir);
		}

		if (resume)
			die(_("Resolve operation not in progress, we are not resuming."));

		for (i = 0; i < argc; i++) {
			if (is_absolute_path(argv[i]) || !prefix)
				argv_array_push(&paths, argv[i]);
			else
				argv_array_push(&paths, mkpath("%s/%s", prefix, argv[i]));
		}

		am_setup(&state, patch_format, paths.argv, keep_cr);

		argv_array_clear(&paths);
	}

	switch (resume) {
	case RESUME_FALSE:
		am_run(&state, 0);
		break;
	case RESUME_APPLY:
		am_run(&state, 1);
		break;
	case RESUME_RESOLVED:
		am_resolve(&state);
		break;
	case RESUME_SKIP:
		am_skip(&state);
		break;
	case RESUME_ABORT:
		am_abort(&state);
		break;
	default:
		die("BUG: invalid resume value");
	}

	am_state_release(&state);

	return 0;
}