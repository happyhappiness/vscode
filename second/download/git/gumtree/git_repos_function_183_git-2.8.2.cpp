int parse_submodule_config_option(const char *var, const char *value)
{
	struct parse_config_parameter parameter;
	parameter.cache = &cache;
	parameter.commit_sha1 = NULL;
	parameter.gitmodules_sha1 = null_sha1;
	parameter.overwrite = 1;

	ensure_cache_init();
	return parse_config(var, value, &parameter);
}