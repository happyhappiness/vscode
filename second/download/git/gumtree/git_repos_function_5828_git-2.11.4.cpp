static int prune(int argc, const char **argv)
{
	int dry_run = 0, result = 0;
	struct option options[] = {
		OPT__DRY_RUN(&dry_run, N_("dry run")),
		OPT_END()
	};

	argc = parse_options(argc, argv, NULL, options, builtin_remote_prune_usage,
			     0);

	if (argc < 1)
		usage_with_options(builtin_remote_prune_usage, options);

	for (; argc; argc--, argv++)
		result |= prune_remote(*argv, dry_run);

	return result;
}