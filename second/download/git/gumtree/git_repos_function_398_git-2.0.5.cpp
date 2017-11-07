int git_config_include(const char *var, const char *value, void *data)
{
	struct config_include_data *inc = data;
	const char *type;
	int ret;

	/*
	 * Pass along all values, including "include" directives; this makes it
	 * possible to query information on the includes themselves.
	 */
	ret = inc->fn(var, value, inc->data);
	if (ret < 0)
		return ret;

	type = skip_prefix(var, "include.");
	if (!type)
		return ret;

	if (!strcmp(type, "path"))
		ret = handle_path_include(value, inc);
	return ret;
}