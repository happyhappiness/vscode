int git_config_get_int(const char *key, int *dest)
{
	git_config_check_init();
	return git_configset_get_int(&the_config_set, key, dest);
}