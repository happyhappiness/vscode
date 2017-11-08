int git_config_get_ulong(const char *key, unsigned long *dest)
{
	git_config_check_init();
	return git_configset_get_ulong(&the_config_set, key, dest);
}