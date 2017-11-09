int option_parse_recurse_submodules_worktree_updater(const struct option *opt,
						     const char *arg, int unset)
{
	if (unset) {
		config_update_recurse_submodules = RECURSE_SUBMODULES_OFF;
		return 0;
	}
	if (arg)
		config_update_recurse_submodules =
			parse_update_recurse_submodules_arg(opt->long_name,
							    arg);
	else
		config_update_recurse_submodules = RECURSE_SUBMODULES_ON;

	return 0;
}