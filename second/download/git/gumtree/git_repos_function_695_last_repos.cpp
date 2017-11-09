int git_configset_get_bool_or_int(struct config_set *cs, const char *key,
				int *is_bool, int *dest)
{
	const char *value;
	if (!git_configset_get_value(cs, key, &value)) {
		*dest = git_config_bool_or_int(key, value, is_bool);
		return 0;
	} else
		return 1;
}