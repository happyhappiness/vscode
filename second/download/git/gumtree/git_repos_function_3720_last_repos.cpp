void load_submodule_cache(void)
{
	if (config_update_recurse_submodules == RECURSE_SUBMODULES_OFF)
		return;

	gitmodules_config();
	git_config(submodule_config, NULL);
}