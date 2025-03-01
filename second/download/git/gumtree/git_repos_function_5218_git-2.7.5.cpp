int cmd_fmt_merge_msg(int argc, const char **argv, const char *prefix)
{
	const char *inpath = NULL;
	const char *message = NULL;
	int shortlog_len = -1;
	struct option options[] = {
		{ OPTION_INTEGER, 0, "log", &shortlog_len, N_("n"),
		  N_("populate log with at most <n> entries from shortlog"),
		  PARSE_OPT_OPTARG, NULL, DEFAULT_MERGE_LOG_LEN },
		{ OPTION_INTEGER, 0, "summary", &shortlog_len, N_("n"),
		  N_("alias for --log (deprecated)"),
		  PARSE_OPT_OPTARG | PARSE_OPT_HIDDEN, NULL,
		  DEFAULT_MERGE_LOG_LEN },
		OPT_STRING('m', "message", &message, N_("text"),
			N_("use <text> as start of message")),
		OPT_FILENAME('F', "file", &inpath, N_("file to read from")),
		OPT_END()
	};

	FILE *in = stdin;
	struct strbuf input = STRBUF_INIT, output = STRBUF_INIT;
	int ret;
	struct fmt_merge_msg_opts opts;

	git_config(fmt_merge_msg_config, NULL);
	argc = parse_options(argc, argv, prefix, options, fmt_merge_msg_usage,
			     0);
	if (argc > 0)
		usage_with_options(fmt_merge_msg_usage, options);
	if (shortlog_len < 0)
		shortlog_len = (merge_log_config > 0) ? merge_log_config : 0;

	if (inpath && strcmp(inpath, "-")) {
		in = fopen(inpath, "r");
		if (!in)
			die_errno("cannot open '%s'", inpath);
	}

	if (strbuf_read(&input, fileno(in), 0) < 0)
		die_errno("could not read input file");

	if (message)
		strbuf_addstr(&output, message);

	memset(&opts, 0, sizeof(opts));
	opts.add_title = !message;
	opts.credit_people = 1;
	opts.shortlog_len = shortlog_len;

	ret = fmt_merge_msg(&input, &output, &opts);
	if (ret)
		return ret;
	write_in_full(STDOUT_FILENO, output.buf, output.len);
	return 0;
}