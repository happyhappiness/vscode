int cmd_replace(int argc, const char **argv, const char *prefix)
{
	int list = 0, delete = 0, force = 0;
	const char *format = NULL;
	struct option options[] = {
		OPT_BOOL('l', "list", &list, N_("list replace refs")),
		OPT_BOOL('d', "delete", &delete, N_("delete replace refs")),
		OPT_BOOL('f', "force", &force, N_("replace the ref if it exists")),
		OPT_STRING(0, "format", &format, N_("format"), N_("use this format")),
		OPT_END()
	};

	check_replace_refs = 0;

	argc = parse_options(argc, argv, prefix, options, git_replace_usage, 0);

	if (list && delete)
		usage_msg_opt("-l and -d cannot be used together",
			      git_replace_usage, options);

	if (format && delete)
		usage_msg_opt("--format and -d cannot be used together",
			      git_replace_usage, options);

	if (force && (list || delete))
		usage_msg_opt("-f cannot be used with -d or -l",
			      git_replace_usage, options);

	/* Delete refs */
	if (delete) {
		if (argc < 1)
			usage_msg_opt("-d needs at least one argument",
				      git_replace_usage, options);
		return for_each_replace_name(argv, delete_replace_ref);
	}

	/* Replace object */
	if (!list && argc) {
		if (argc != 2)
			usage_msg_opt("bad number of arguments",
				      git_replace_usage, options);
		if (format)
			usage_msg_opt("--format cannot be used when not listing",
				      git_replace_usage, options);
		return replace_object(argv[0], argv[1], force);
	}

	/* List refs, even if "list" is not set */
	if (argc > 1)
		usage_msg_opt("only one pattern can be given with -l",
			      git_replace_usage, options);
	if (force)
		usage_msg_opt("-f needs some arguments",
			      git_replace_usage, options);

	return list_replace_refs(argv[0], format);
}