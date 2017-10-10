	else if (!strcmp(arg, "--follow"))
		DIFF_OPT_SET(options, FOLLOW_RENAMES);
	else if (!strcmp(arg, "--no-follow"))
		DIFF_OPT_CLR(options, FOLLOW_RENAMES);
	else if (!strcmp(arg, "--color"))
		options->use_color = 1;
	else if (skip_prefix(arg, "--color=", &arg)) {
		int value = git_config_colorbool(NULL, arg);
		if (value < 0)
			return error("option `color' expects \"always\", \"auto\", or \"never\"");
		options->use_color = value;
	}
	else if (!strcmp(arg, "--no-color"))
		options->use_color = 0;
	else if (!strcmp(arg, "--color-words")) {
		options->use_color = 1;
		options->word_diff = DIFF_WORDS_COLOR;
	}
	else if (skip_prefix(arg, "--color-words=", &arg)) {
		options->use_color = 1;
		options->word_diff = DIFF_WORDS_COLOR;
		options->word_regex = arg;
	}
	else if (!strcmp(arg, "--word-diff")) {
		if (options->word_diff == DIFF_WORDS_NONE)
			options->word_diff = DIFF_WORDS_PLAIN;
	}
	else if (skip_prefix(arg, "--word-diff=", &arg)) {
		if (!strcmp(arg, "plain"))
			options->word_diff = DIFF_WORDS_PLAIN;
		else if (!strcmp(arg, "color")) {
			options->use_color = 1;
			options->word_diff = DIFF_WORDS_COLOR;
		}
		else if (!strcmp(arg, "porcelain"))
			options->word_diff = DIFF_WORDS_PORCELAIN;
		else if (!strcmp(arg, "none"))
			options->word_diff = DIFF_WORDS_NONE;
		else
			die("bad --word-diff argument: %s", arg);
	}
	else if ((argcount = parse_long_opt("word-diff-regex", av, &optarg))) {
		if (options->word_diff == DIFF_WORDS_NONE)
			options->word_diff = DIFF_WORDS_PLAIN;
		options->word_regex = optarg;
		return argcount;
