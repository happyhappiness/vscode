static void cmd_log_init_finish(int argc, const char **argv, const char *prefix,
			 struct rev_info *rev, struct setup_revision_opt *opt)
{
	struct userformat_want w;
	int quiet = 0, source = 0, mailmap = 0;
	static struct line_opt_callback_data line_cb = {NULL, NULL, STRING_LIST_INIT_DUP};

	const struct option builtin_log_options[] = {
		OPT__QUIET(&quiet, N_("suppress diff output")),
		OPT_BOOL(0, "source", &source, N_("show source")),
		OPT_BOOL(0, "use-mailmap", &mailmap, N_("Use mail map file")),
		{ OPTION_CALLBACK, 0, "decorate", NULL, NULL, N_("decorate options"),
		  PARSE_OPT_OPTARG, decorate_callback},
		OPT_CALLBACK('L', NULL, &line_cb, "n,m:file",
			     "Process line range n,m in file, counting from 1",
			     log_line_range_callback),
		OPT_END()
	};

	line_cb.rev = rev;
	line_cb.prefix = prefix;

	mailmap = use_mailmap_config;
	argc = parse_options(argc, argv, prefix,
			     builtin_log_options, builtin_log_usage,
			     PARSE_OPT_KEEP_ARGV0 | PARSE_OPT_KEEP_UNKNOWN |
			     PARSE_OPT_KEEP_DASHDASH);

	if (quiet)
		rev->diffopt.output_format |= DIFF_FORMAT_NO_OUTPUT;
	argc = setup_revisions(argc, argv, rev, opt);

	/* Any arguments at this point are not recognized */
	if (argc > 1)
		die("unrecognized argument: %s", argv[1]);

	memset(&w, 0, sizeof(w));
	userformat_find_requirements(NULL, &w);

	if (!rev->show_notes_given && (!rev->pretty_given || w.notes))
		rev->show_notes = 1;
	if (rev->show_notes)
		init_display_notes(&rev->notes_opt);

	if (rev->diffopt.pickaxe || rev->diffopt.filter ||
	    DIFF_OPT_TST(&rev->diffopt, FOLLOW_RENAMES))
		rev->always_show_header = 0;

	if (source)
		rev->show_source = 1;

	if (mailmap) {
		rev->mailmap = xcalloc(1, sizeof(struct string_list));
		read_mailmap(rev->mailmap, NULL);
	}

	if (rev->pretty_given && rev->commit_format == CMIT_FMT_RAW) {
		/*
		 * "log --pretty=raw" is special; ignore UI oriented
		 * configuration variables such as decoration.
		 */
		if (!decoration_given)
			decoration_style = 0;
		if (!rev->abbrev_commit_given)
			rev->abbrev_commit = 0;
	}

	if (decoration_style) {
		rev->show_decorations = 1;
		load_ref_decorations(decoration_style);
	}

	if (rev->line_level_traverse)
		line_log_init(rev, line_cb.prefix, &line_cb.args);

	setup_pager();
}