int cmd_remote(int argc, const char **argv, const char *prefix)
{
	struct option options[] = {
		OPT__VERBOSE(&verbose, N_("be verbose; must be placed before a subcommand")),
		OPT_END()
	};
	int result;

	argc = parse_options(argc, argv, prefix, options, builtin_remote_usage,
		PARSE_OPT_STOP_AT_NON_OPTION);

	if (argc < 1)
		result = show_all();
	else if (!strcmp(argv[0], "add"))
		result = add(argc, argv);
	else if (!strcmp(argv[0], "rename"))
		result = mv(argc, argv);
	else if (!strcmp(argv[0], "rm") || !strcmp(argv[0], "remove"))
		result = rm(argc, argv);
	else if (!strcmp(argv[0], "set-head"))
		result = set_head(argc, argv);
	else if (!strcmp(argv[0], "set-branches"))
		result = set_branches(argc, argv);
	else if (!strcmp(argv[0], "set-url"))
		result = set_url(argc, argv);
	else if (!strcmp(argv[0], "show"))
		result = show(argc, argv);
	else if (!strcmp(argv[0], "prune"))
		result = prune(argc, argv);
	else if (!strcmp(argv[0], "update"))
		result = update(argc, argv);
	else {
		error(_("Unknown subcommand: %s"), argv[0]);
		usage_with_options(builtin_remote_usage, options);
	}

	return result ? 1 : 0;
}