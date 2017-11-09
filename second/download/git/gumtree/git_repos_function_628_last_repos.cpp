int git_config_include(const char *var, const char *value, void *data)
{
	struct config_include_data *inc = data;
	const char *cond, *key;
	int cond_len;
	int ret;

	/*
	 * Pass along all values, including "include" directives; this makes it
	 * possible to query information on the includes themselves.
	 */
	ret = inc->fn(var, value, inc->data);
	if (ret < 0)
		return ret;

	if (!strcmp(var, "include.path"))
		ret = handle_path_include(value, inc);

	if (!parse_config_key(var, "includeif", &cond, &cond_len, &key) &&
	    (cond && include_condition_is_true(inc->opts, cond, cond_len)) &&
	    !strcmp(key, "path"))
		ret = handle_path_include(value, inc);

	return ret;
}