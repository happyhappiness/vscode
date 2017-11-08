int git_config_get_value(const char *key, const char **value)
{
	git_config_check_init();
	return git_configset_get_value(&the_config_set, key, value);
}