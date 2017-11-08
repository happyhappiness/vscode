static int cmd_parseopt(int argc, const char **argv, const char *prefix)
{
	static int keep_dashdash = 0, stop_at_non_option = 0;
	static char const * const parseopt_usage[] = {
		N_("git rev-parse --parseopt [<options>] -- [<args>...]"),
		NULL
	};
	static struct option parseopt_opts[] = {
		OPT_BOOL(0, "keep-dashdash", &keep_dashdash,
					N_("keep the `--` passed as an arg")),
		OPT_BOOL(0, "stop-at-non-option", &stop_at_non_option,
					N_("stop parsing after the "
					   "first non-option argument")),
		OPT_BOOL(0, "stuck-long", &stuck_long,
					N_("output in stuck long form")),
		OPT_END(),
	};
	static const char * const flag_chars = "*=?!";

	struct strbuf sb = STRBUF_INIT, parsed = STRBUF_INIT;
	const char **usage = NULL;
	struct option *opts = NULL;
	int onb = 0, osz = 0, unb = 0, usz = 0;

	strbuf_addstr(&parsed, "set --");
	argc = parse_options(argc, argv, prefix, parseopt_opts, parseopt_usage,
	                     PARSE_OPT_KEEP_DASHDASH);
	if (argc < 1 || strcmp(argv[0], "--"))
		usage_with_options(parseopt_usage, parseopt_opts);

	/* get the usage up to the first line with a -- on it */
	for (;;) {
		if (strbuf_getline(&sb, stdin) == EOF)
			die("premature end of input");
		ALLOC_GROW(usage, unb + 1, usz);
		if (!strcmp("--", sb.buf)) {
			if (unb < 1)
				die("no usage string given before the `--' separator");
			usage[unb] = NULL;
			break;
		}
		usage[unb++] = strbuf_detach(&sb, NULL);
	}

	/* parse: (<short>|<short>,<long>|<long>)[*=?!]*<arghint>? SP+ <help> */
	while (strbuf_getline(&sb, stdin) != EOF) {
		const char *s;
		const char *help;
		struct option *o;

		if (!sb.len)
			continue;

		ALLOC_GROW(opts, onb + 1, osz);
		memset(opts + onb, 0, sizeof(opts[onb]));

		o = &opts[onb++];
		help = strchr(sb.buf, ' ');
		if (!help || *sb.buf == ' ') {
			o->type = OPTION_GROUP;
			o->help = xstrdup(skipspaces(sb.buf));
			continue;
		}

		o->type = OPTION_CALLBACK;
		o->help = xstrdup(skipspaces(help));
		o->value = &parsed;
		o->flags = PARSE_OPT_NOARG;
		o->callback = &parseopt_dump;

		/* name(s) */
		s = strpbrk(sb.buf, flag_chars);
		if (s == NULL)
			s = help;

		if (s - sb.buf == 1) /* short option only */
			o->short_name = *sb.buf;
		else if (sb.buf[1] != ',') /* long option only */
			o->long_name = xmemdupz(sb.buf, s - sb.buf);
		else {
			o->short_name = *sb.buf;
			o->long_name = xmemdupz(sb.buf + 2, s - sb.buf - 2);
		}

		/* flags */
		while (s < help) {
			switch (*s++) {
			case '=':
				o->flags &= ~PARSE_OPT_NOARG;
				continue;
			case '?':
				o->flags &= ~PARSE_OPT_NOARG;
				o->flags |= PARSE_OPT_OPTARG;
				continue;
			case '!':
				o->flags |= PARSE_OPT_NONEG;
				continue;
			case '*':
				o->flags |= PARSE_OPT_HIDDEN;
				continue;
			}
			s--;
			break;
		}

		if (s < help)
			o->argh = xmemdupz(s, help - s);
	}
	strbuf_release(&sb);

	/* put an OPT_END() */
	ALLOC_GROW(opts, onb + 1, osz);
	memset(opts + onb, 0, sizeof(opts[onb]));
	argc = parse_options(argc, argv, prefix, opts, usage,
			(keep_dashdash ? PARSE_OPT_KEEP_DASHDASH : 0) |
			(stop_at_non_option ? PARSE_OPT_STOP_AT_NON_OPTION : 0) |
			PARSE_OPT_SHELL_EVAL);

	strbuf_addstr(&parsed, " --");
	sq_quote_argv(&parsed, argv, 0);
	puts(parsed.buf);
	return 0;
}