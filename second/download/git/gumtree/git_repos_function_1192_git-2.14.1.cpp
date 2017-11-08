static int config_alias_cb(const char *key, const char *value, void *d)
{
	struct config_alias_data *data = d;
	const char *p;

	if (skip_prefix(key, "alias.", &p) && !strcasecmp(p, data->alias))
		return git_config_string((const char **)&data->v, key, value);

	return 0;
}