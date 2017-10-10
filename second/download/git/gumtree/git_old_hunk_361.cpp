
	git_config(git_fetch_config, NULL);

	argc = parse_options(argc, argv, prefix,
			     builtin_fetch_options, builtin_fetch_usage, 0);

	if (unshallow) {
		if (depth)
			die(_("--depth and --unshallow cannot be used together"));
		else if (!is_repository_shallow())
			die(_("--unshallow on a complete repository does not make sense"));
		else
			depth = xstrfmt("%d", INFINITE_DEPTH);
	}

	/* no need to be strict, transport_set_option() will validate it again */
	if (depth && atoi(depth) < 1)
		die(_("depth %s is not a positive number"), depth);

	if (recurse_submodules != RECURSE_SUBMODULES_OFF) {
		if (recurse_submodules_default) {
			int arg = parse_fetch_recurse_submodules_arg("--recurse-submodules-default", recurse_submodules_default);
			set_config_fetch_recurse_submodules(arg);
		}
