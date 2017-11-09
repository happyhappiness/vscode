static int update(int argc, const char **argv)
{
	int i, prune = -1;
	struct option options[] = {
		OPT_BOOL('p', "prune", &prune,
			 N_("prune remotes after fetching")),
		OPT_END()
	};
	struct argv_array fetch_argv = ARGV_ARRAY_INIT;
	int default_defined = 0;
	int retval;

	argc = parse_options(argc, argv, NULL, options, builtin_remote_update_usage,
			     PARSE_OPT_KEEP_ARGV0);

	argv_array_push(&fetch_argv, "fetch");

	if (prune != -1)
		argv_array_push(&fetch_argv, prune ? "--prune" : "--no-prune");
	if (verbose)
		argv_array_push(&fetch_argv, "-v");
	argv_array_push(&fetch_argv, "--multiple");
	if (argc < 2)
		argv_array_push(&fetch_argv, "default");
	for (i = 1; i < argc; i++)
		argv_array_push(&fetch_argv, argv[i]);

	if (strcmp(fetch_argv.argv[fetch_argv.argc-1], "default") == 0) {
		git_config(get_remote_default, &default_defined);
		if (!default_defined) {
			argv_array_pop(&fetch_argv);
			argv_array_push(&fetch_argv, "--all");
		}
	}

	retval = run_command_v_opt(fetch_argv.argv, RUN_GIT_CMD);
	argv_array_clear(&fetch_argv);
	return retval;
}