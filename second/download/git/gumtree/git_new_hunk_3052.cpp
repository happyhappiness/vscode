		DIFF_OPT_SET(options, FUNCCONTEXT);
	else if (!strcmp(arg, "--function-context"))
		DIFF_OPT_SET(options, FUNCCONTEXT);
	else if (!strcmp(arg, "--no-function-context"))
		DIFF_OPT_CLR(options, FUNCCONTEXT);
	else if ((argcount = parse_long_opt("output", av, &optarg))) {
		const char *path = prefix_filename(prefix, strlen(prefix), optarg);
		options->file = fopen(path, "w");
		if (!options->file)
			die_errno("Could not open '%s'", path);
		options->close_file = 1;
		return argcount;
	} else
		return 0;
	return 1;
}
