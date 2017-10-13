int git_config_get_string_const(const char *key, const char **dest)
{
	int ret;
	git_config_check_init();
	ret = git_configset_get_string_const(&the_config_set, key, dest);
	if (ret < 0)
		git_die_config(key, NULL);
	return ret;
}