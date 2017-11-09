int git_default_submodule_config(const char *var, const char *value, void *cb)
{
	if (!strcmp(var, "submodule.recurse")) {
		int v = git_config_bool(var, value) ?
			RECURSE_SUBMODULES_ON : RECURSE_SUBMODULES_OFF;
		config_update_recurse_submodules = v;
	}
	return 0;
}