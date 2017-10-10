
		OPT_GROUP(""),
		OPT_INTEGER( 0 , "count", &maxcount, N_("show only <n> matched refs")),
		OPT_STRING(  0 , "format", &format, N_("format"), N_("format to use for the output")),
		OPT_CALLBACK(0 , "sort", sorting_tail, N_("key"),
			    N_("field name to sort on"), &parse_opt_ref_sorting),
		OPT_END(),
	};

	parse_options(argc, argv, prefix, opts, for_each_ref_usage, 0);
	if (maxcount < 0) {
		error("invalid --count argument: `%d'", maxcount);
		usage_with_options(for_each_ref_usage, opts);
	}
	if (HAS_MULTI_BITS(quote_style)) {
