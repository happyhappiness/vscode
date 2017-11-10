int cmd_shortlog(int argc, const char **argv, const char *prefix)
{
	struct shortlog log = { STRING_LIST_INIT_NODUP };
	struct rev_info rev;
	int nongit = !startup_info->have_repository;

	const struct option options[] = {
		OPT_BOOL('c', "committer", &log.committer,
			 N_("Group by committer rather than author")),
		OPT_BOOL('n', "numbered", &log.sort_by_number,
			 N_("sort output according to the number of commits per author")),
		OPT_BOOL('s', "summary", &log.summary,
			 N_("Suppress commit descriptions, only provides commit count")),
		OPT_BOOL('e', "email", &log.email,
			 N_("Show the email address of each author")),
		{ OPTION_CALLBACK, 'w', NULL, &log, N_("w[,i1[,i2]]"),
			N_("Linewrap output"), PARSE_OPT_OPTARG, &parse_wrap_args },
		OPT_END(),
	};

	struct parse_opt_ctx_t ctx;

	git_config(git_default_config, NULL);
	shortlog_init(&log);
	init_revisions(&rev, prefix);
	parse_options_start(&ctx, argc, argv, prefix, options,
			    PARSE_OPT_KEEP_DASHDASH | PARSE_OPT_KEEP_ARGV0);

	for (;;) {
		switch (parse_options_step(&ctx, options, shortlog_usage)) {
		case PARSE_OPT_HELP:
			exit(129);
		case PARSE_OPT_DONE:
			goto parse_done;
		}
		parse_revision_opt(&rev, &ctx, options, shortlog_usage);
	}
parse_done:
	argc = parse_options_end(&ctx);

	if (setup_revisions(argc, argv, &rev, NULL) != 1) {
		error(_("unrecognized argument: %s"), argv[1]);
		usage_with_options(shortlog_usage, options);
	}

	log.user_format = rev.commit_format == CMIT_FMT_USERFORMAT;
	log.abbrev = rev.abbrev;
	log.file = rev.diffopt.file;

	/* assume HEAD if from a tty */
	if (!nongit && !rev.pending.nr && isatty(0))
		add_head_to_pending(&rev);
	if (rev.pending.nr == 0) {
		if (isatty(0))
			fprintf(stderr, _("(reading log message from standard input)\n"));
		read_from_stdin(&log);
	}
	else
		get_from_rev(&rev, &log);

	shortlog_output(&log);
	if (log.file != stdout)
		fclose(log.file);
	return 0;
}