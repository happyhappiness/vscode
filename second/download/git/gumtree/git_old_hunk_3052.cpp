		DIFF_OPT_SET(options, FUNCCONTEXT);
	else if (!strcmp(arg, "--function-context"))
		DIFF_OPT_SET(options, FUNCCONTEXT);
	else if (!strcmp(arg, "--no-function-context"))
		DIFF_OPT_CLR(options, FUNCCONTEXT);
	else if ((argcount = parse_long_opt("output", av, &optarg))) {
		options->file = fopen(optarg, "w");
		if (!options->file)
			die_errno("Could not open '%s'", optarg);
		options->close_file = 1;
		return argcount;
	} else
		return 0;
	return 1;
}
