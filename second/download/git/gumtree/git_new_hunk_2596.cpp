	else if (!strcmp(arg, "-R"))
		DIFF_OPT_SET(options, REVERSE_DIFF);
	else if (!strcmp(arg, "--find-copies-harder"))
		DIFF_OPT_SET(options, FIND_COPIES_HARDER);
	else if (!strcmp(arg, "--follow"))
		DIFF_OPT_SET(options, FOLLOW_RENAMES);
	else if (!strcmp(arg, "--no-follow")) {
		DIFF_OPT_CLR(options, FOLLOW_RENAMES);
		DIFF_OPT_CLR(options, DEFAULT_FOLLOW_RENAMES);
	} else if (!strcmp(arg, "--color"))
		options->use_color = 1;
	else if (skip_prefix(arg, "--color=", &arg)) {
		int value = git_config_colorbool(NULL, arg);
		if (value < 0)
			return error("option `color' expects \"always\", \"auto\", or \"never\"");
		options->use_color = value;
