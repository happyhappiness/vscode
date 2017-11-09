int git_configset_get_maybe_bool(struct config_set *cs, const char *key, int *dest)
{
	const char *value;
	if (!git_configset_get_value(cs, key, &value)) {
		*dest = git_config_maybe_bool(key, value);
		if (*dest == -1)
			return -1;
		return 0;
	} else
		return 1;
}