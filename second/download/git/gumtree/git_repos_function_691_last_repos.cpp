int git_configset_get_string(struct config_set *cs, const char *key, char **dest)
{
	return git_configset_get_string_const(cs, key, (const char **)dest);
}