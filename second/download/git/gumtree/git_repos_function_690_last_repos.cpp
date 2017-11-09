int git_configset_get_string_const(struct config_set *cs, const char *key, const char **dest)
{
	const char *value;
	if (!git_configset_get_value(cs, key, &value))
		return git_config_string(dest, key, value);
	else
		return 1;
}