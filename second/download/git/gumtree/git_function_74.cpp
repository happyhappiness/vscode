int cmd_replace(int argc, const char **argv, const char *prefix)
{
	int force = 0;
	int raw = 0;
	const char *format = NULL;
	enum {
		MODE_UNSPECIFIED = 0,
		MODE_LIST,
		MODE_DELETE,
		MODE_EDIT,
		MODE_GRAFT,
		MODE_REPLACE
	} cmdmode = MODE_UNSPECIFIED;
	struct option options[] = {
		OPT_CMDMODE('l', "list", &cmdmode, N_("list replace refs"), MODE_LIST),
		OPT_CMDMODE('d', "delete", &cmdmode, N_("delete replace refs"), MODE_DELETE),
		OPT_CMDMODE('e', "edit", &cmdmode, N_("edit existing object"), MODE_EDIT),
		OPT_CMDMODE('g', "graft", &cmdmode, N_("change a commit's parents"), MODE_GRAFT),
		OPT_BOOL('f', "force", &force, N_("replace the ref if it exists")),
		OPT_BOOL(0, "raw", &raw, N_("do not pretty-print contents for --edit")),
		OPT_STRING(0, "format", &format, N_("format"), N_("use this format")),
		OPT_END()
	};

	check_replace_refs = 0;

	argc = parse_options(argc, argv, prefix, options, git_replace_usage, 0);

	if (!cmdmode)
		cmdmode = argc ? MODE_REPLACE : MODE_LIST;

	if (format && cmdmode != MODE_LIST)
		usage_msg_opt("--format cannot be used when not listing",
			      git_replace_usage, options);

	if (force &&
	    cmdmode != MODE_REPLACE &&
	    cmdmode != MODE_EDIT &&
	    cmdmode != MODE_GRAFT)
		usage_msg_opt("-f only makes sense when writing a replacement",
			      git_replace_usage, options);

	if (raw && cmdmode != MODE_EDIT)
		usage_msg_opt("--raw only makes sense with --edit",
			      git_replace_usage, options);

	switch (cmdmode) {
	case MODE_DELETE:
		if (argc < 1)
			usage_msg_opt("-d needs at least one argument",
				      git_replace_usage, options);
		return for_each_replace_name(argv, delete_replace_ref);

	case MODE_REPLACE:
		if (argc != 2)
			usage_msg_opt("bad number of arguments",
				      git_replace_usage, options);
		return replace_object(argv[0], argv[1], force);

	case MODE_EDIT:
		if (argc != 1)
			usage_msg_opt("-e needs exactly one argument",
				      git_replace_usage, options);
		return edit_and_replace(argv[0], force, raw);

	case MODE_GRAFT:
		if (argc < 1)
			usage_msg_opt("-g needs at least one argument",
				      git_replace_usage, options);
		return create_graft(argc, argv, force);

	case MODE_LIST:
		if (argc > 1)
			usage_msg_opt("only one pattern can be given with -l",
				      git_replace_usage, options);
		return list_replace_refs(argv[0], format);

	default:
		die("BUG: invalid cmdmode %d", (int)cmdmode);
	}
}