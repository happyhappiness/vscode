int cmd_interpret_trailers(int argc, const char **argv, const char *prefix)
{
	int in_place = 0;
	int trim_empty = 0;
	struct string_list trailers = STRING_LIST_INIT_DUP;

	struct option options[] = {
		OPT_BOOL(0, "in-place", &in_place, N_("edit files in place")),
		OPT_BOOL(0, "trim-empty", &trim_empty, N_("trim empty trailers")),
		OPT_STRING_LIST(0, "trailer", &trailers, N_("trailer"),
				N_("trailer(s) to add")),
		OPT_END()
	};

	argc = parse_options(argc, argv, prefix, options,
			     git_interpret_trailers_usage, 0);

	if (argc) {
		int i;
		for (i = 0; i < argc; i++)
			process_trailers(argv[i], in_place, trim_empty, &trailers);
	} else {
		if (in_place)
			die(_("no input file given for in-place editing"));
		process_trailers(NULL, in_place, trim_empty, &trailers);
	}

	string_list_clear(&trailers, 0);

	return 0;
}