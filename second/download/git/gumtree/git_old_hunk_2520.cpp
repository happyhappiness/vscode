		OPT_BIT(0 , "tcl",  &quote_style,
			N_("quote placeholders suitably for Tcl"), QUOTE_TCL),

		OPT_GROUP(""),
		OPT_INTEGER( 0 , "count", &maxcount, N_("show only <n> matched refs")),
		OPT_STRING(  0 , "format", &format, N_("format"), N_("format to use for the output")),
		OPT_CALLBACK(0 , "sort", sort_tail, N_("key"),
			    N_("field name to sort on"), &opt_parse_sort),
		OPT_END(),
	};

	parse_options(argc, argv, prefix, opts, for_each_ref_usage, 0);
	if (maxcount < 0) {
		error("invalid --count argument: `%d'", maxcount);
		usage_with_options(for_each_ref_usage, opts);
	}
	if (HAS_MULTI_BITS(quote_style)) {
		error("more than one quoting style?");
		usage_with_options(for_each_ref_usage, opts);
	}
	if (verify_format(format))
		usage_with_options(for_each_ref_usage, opts);

	if (!sort)
		sort = default_sort();

	/* for warn_ambiguous_refs */
	git_config(git_default_config, NULL);

	memset(&cbdata, 0, sizeof(cbdata));
	cbdata.grab_pattern = argv;
	for_each_rawref(grab_single_ref, &cbdata);
	refs = cbdata.grab_array;
	num_refs = cbdata.grab_cnt;

	sort_refs(sort, refs, num_refs);

	if (!maxcount || num_refs < maxcount)
		maxcount = num_refs;
	for (i = 0; i < maxcount; i++)
		show_ref(refs[i], format, quote_style);
	return 0;
}
