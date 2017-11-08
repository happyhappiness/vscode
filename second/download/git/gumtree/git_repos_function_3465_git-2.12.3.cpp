int is_submodule_initialized(const char *path)
{
	int ret = 0;
	const struct submodule *module = NULL;

	module = submodule_from_path(null_sha1, path);

	if (module) {
		char *key = xstrfmt("submodule.%s.url", module->name);
		char *value = NULL;

		ret = !git_config_get_string(key, &value);

		free(value);
		free(key);
	}

	return ret;
}