int git_config_get_bool_or_int(const char *key, int *is_bool, int *dest)
{
	git_config_check_init();
	return git_configset_get_bool_or_int(&the_config_set, key, is_bool, dest);
}