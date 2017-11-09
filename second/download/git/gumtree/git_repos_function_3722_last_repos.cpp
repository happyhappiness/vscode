static int gitmodules_cb(const char *var, const char *value, void *data)
{
	struct repository *repo = data;
	return submodule_config_option(repo, var, value);
}