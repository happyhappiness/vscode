	if (depth && atoi(depth) < 1)
		die(_("depth %s is not a positive number"), depth);
	if (depth || deepen_since || deepen_not.nr)
		deepen = 1;

	if (recurse_submodules != RECURSE_SUBMODULES_OFF) {
		set_config_fetch_recurse_submodules(recurse_submodules_default);
		gitmodules_config();
		git_config(submodule_config, NULL);
	}

	if (all) {
		if (argc == 1)
