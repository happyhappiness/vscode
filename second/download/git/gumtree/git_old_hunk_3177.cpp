	                     PARSE_OPT_KEEP_DASHDASH);
	if (argc < 1 || strcmp(argv[0], "--"))
		usage_with_options(parseopt_usage, parseopt_opts);

	/* get the usage up to the first line with a -- on it */
	for (;;) {
		if (strbuf_getline(&sb, stdin, '\n') == EOF)
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
	while (strbuf_getline(&sb, stdin, '\n') != EOF) {
		const char *s;
		const char *help;
		struct option *o;

		if (!sb.len)
			continue;
