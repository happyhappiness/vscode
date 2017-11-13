int cmd_apply(int argc, const char **argv, const char *prefix_)
{
	int i;
	int errs = 0;
	int is_not_gitdir = !startup_info->have_repository;
	int force_apply = 0;

	const char *whitespace_option = NULL;

	struct option builtin_apply_options[] = {
		{ OPTION_CALLBACK, 0, "exclude", NULL, N_("path"),
			N_("don't apply changes matching the given path"),
			0, option_parse_exclude },
		{ OPTION_CALLBACK, 0, "include", NULL, N_("path"),
			N_("apply changes matching the given path"),
			0, option_parse_include },
		{ OPTION_CALLBACK, 'p', NULL, NULL, N_("num"),
			N_("remove <num> leading slashes from traditional diff paths"),
			0, option_parse_p },
		OPT_BOOL(0, "no-add", &no_add,
			N_("ignore additions made by the patch")),
		OPT_BOOL(0, "stat", &diffstat,
			N_("instead of applying the patch, output diffstat for the input")),
		OPT_NOOP_NOARG(0, "allow-binary-replacement"),
		OPT_NOOP_NOARG(0, "binary"),
		OPT_BOOL(0, "numstat", &numstat,
			N_("show number of added and deleted lines in decimal notation")),
		OPT_BOOL(0, "summary", &summary,
			N_("instead of applying the patch, output a summary for the input")),
		OPT_BOOL(0, "check", &check,
			N_("instead of applying the patch, see if the patch is applicable")),
		OPT_BOOL(0, "index", &check_index,
			N_("make sure the patch is applicable to the current index")),
		OPT_BOOL(0, "cached", &cached,
			N_("apply a patch without touching the working tree")),
		OPT_BOOL(0, "unsafe-paths", &unsafe_paths,
			N_("accept a patch that touches outside the working area")),
		OPT_BOOL(0, "apply", &force_apply,
			N_("also apply the patch (use with --stat/--summary/--check)")),
		OPT_BOOL('3', "3way", &threeway,
			 N_( "attempt three-way merge if a patch does not apply")),
		OPT_FILENAME(0, "build-fake-ancestor", &fake_ancestor,
			N_("build a temporary index based on embedded index information")),
		/* Think twice before adding "--nul" synonym to this */
		OPT_SET_INT('z', NULL, &line_termination,
			N_("paths are separated with NUL character"), '\0'),
		OPT_INTEGER('C', NULL, &p_context,
				N_("ensure at least <n> lines of context match")),
		{ OPTION_CALLBACK, 0, "whitespace", &whitespace_option, N_("action"),
			N_("detect new or modified lines that have whitespace errors"),
			0, option_parse_whitespace },
		{ OPTION_CALLBACK, 0, "ignore-space-change", NULL, NULL,
			N_("ignore changes in whitespace when finding context"),
			PARSE_OPT_NOARG, option_parse_space_change },
		{ OPTION_CALLBACK, 0, "ignore-whitespace", NULL, NULL,
			N_("ignore changes in whitespace when finding context"),
			PARSE_OPT_NOARG, option_parse_space_change },
		OPT_BOOL('R', "reverse", &apply_in_reverse,
			N_("apply the patch in reverse")),
		OPT_BOOL(0, "unidiff-zero", &unidiff_zero,
			N_("don't expect at least one line of context")),
		OPT_BOOL(0, "reject", &apply_with_reject,
			N_("leave the rejected hunks in corresponding *.rej files")),
		OPT_BOOL(0, "allow-overlap", &allow_overlap,
			N_("allow overlapping hunks")),
		OPT__VERBOSE(&apply_verbosely, N_("be verbose")),
		OPT_BIT(0, "inaccurate-eof", &options,
			N_("tolerate incorrectly detected missing new-line at the end of file"),
			INACCURATE_EOF),
		OPT_BIT(0, "recount", &options,
			N_("do not trust the line counts in the hunk headers"),
			RECOUNT),
		{ OPTION_CALLBACK, 0, "directory", NULL, N_("root"),
			N_("prepend <root> to all filenames"),
			0, option_parse_directory },
		OPT_END()
	};

	prefix = prefix_;
	prefix_length = prefix ? strlen(prefix) : 0;
	git_apply_config();
	if (apply_default_whitespace)
		parse_whitespace_option(apply_default_whitespace);
	if (apply_default_ignorewhitespace)
		parse_ignorewhitespace_option(apply_default_ignorewhitespace);

	argc = parse_options(argc, argv, prefix, builtin_apply_options,
			apply_usage, 0);

	if (apply_with_reject && threeway)
		die("--reject and --3way cannot be used together.");
	if (cached && threeway)
		die("--cached and --3way cannot be used together.");
	if (threeway) {
		if (is_not_gitdir)
			die(_("--3way outside a repository"));
		check_index = 1;
	}
	if (apply_with_reject)
		apply = apply_verbosely = 1;
	if (!force_apply && (diffstat || numstat || summary || check || fake_ancestor))
		apply = 0;
	if (check_index && is_not_gitdir)
		die(_("--index outside a repository"));
	if (cached) {
		if (is_not_gitdir)
			die(_("--cached outside a repository"));
		check_index = 1;
	}
	if (check_index)
		unsafe_paths = 0;

	for (i = 0; i < argc; i++) {
		const char *arg = argv[i];
		int fd;

		if (!strcmp(arg, "-")) {
			errs |= apply_patch(0, "<stdin>", options);
			read_stdin = 0;
			continue;
		} else if (0 < prefix_length)
			arg = prefix_filename(prefix, prefix_length, arg);

		fd = open(arg, O_RDONLY);
		if (fd < 0)
			die_errno(_("can't open patch '%s'"), arg);
		read_stdin = 0;
		set_default_whitespace_mode(whitespace_option);
		errs |= apply_patch(fd, arg, options);
		close(fd);
	}
	set_default_whitespace_mode(whitespace_option);
	if (read_stdin)
		errs |= apply_patch(0, "<stdin>", options);
	if (whitespace_error) {
		if (squelch_whitespace_errors &&
		    squelch_whitespace_errors < whitespace_error) {
			int squelched =
				whitespace_error - squelch_whitespace_errors;
			warning(Q_("squelched %d whitespace error",
				   "squelched %d whitespace errors",
				   squelched),
				squelched);
		}
		if (ws_error_action == die_on_ws_error)
			die(Q_("%d line adds whitespace errors.",
			       "%d lines add whitespace errors.",
			       whitespace_error),
			    whitespace_error);
		if (applied_after_fixing_ws && apply)
			warning("%d line%s applied after"
				" fixing whitespace errors.",
				applied_after_fixing_ws,
				applied_after_fixing_ws == 1 ? "" : "s");
		else if (whitespace_error)
			warning(Q_("%d line adds whitespace errors.",
				   "%d lines add whitespace errors.",
				   whitespace_error),
				whitespace_error);
	}

	if (update_index) {
		if (write_locked_index(&the_index, &lock_file, COMMIT_LOCK))
			die(_("Unable to write new index file"));
	}

	return !!errs;
}