void git_config_clear(void)
{
	if (!the_config_set.hash_initialized)
		return;
	git_configset_clear(&the_config_set);
}