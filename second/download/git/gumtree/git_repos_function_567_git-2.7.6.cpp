int git_configset_get_ulong(struct config_set *cs, const char *key, unsigned long *dest)
{
	const char *value;
	if (!git_configset_get_value(cs, key, &value)) {
		*dest = git_config_ulong(key, value);
		return 0;
	} else
		return 1;
}