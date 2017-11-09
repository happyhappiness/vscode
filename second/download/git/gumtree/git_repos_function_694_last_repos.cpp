int git_configset_get_bool(struct config_set *cs, const char *key, int *dest)
{
	const char *value;
	if (!git_configset_get_value(cs, key, &value)) {
		*dest = git_config_bool(key, value);
		return 0;
	} else
		return 1;
}