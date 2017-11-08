int git_config_get_maybe_bool(const char *key, int *dest)
{
	git_config_check_init();
	return git_configset_get_maybe_bool(&the_config_set, key, dest);
}