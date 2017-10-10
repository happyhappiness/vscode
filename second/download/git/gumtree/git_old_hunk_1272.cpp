	if (depth && atoi(depth) < 1)
		die(_("depth %s is not a positive number"), depth);
	if (depth || deepen_since || deepen_not.nr)
		deepen = 1;

	if (recurse_submodules != RECURSE_SUBMODULES_OFF) {
		if (recurse_submodules_default) {
			int arg = parse_fetch_recurse_submodules_arg("--recurse-submodules-default", recurse_submodules_default);
			set_config_fetch_recurse_submodules(arg);
		}
		gitmodules_config();
		git_config(submodule_config, NULL);
	}

	if (all) {
		if (argc == 1)
