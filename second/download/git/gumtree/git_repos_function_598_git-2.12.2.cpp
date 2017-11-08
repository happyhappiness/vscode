static void git_config_check_init(void)
{
	if (the_config_set.hash_initialized)
		return;
	git_configset_init(&the_config_set);
	git_config_raw(config_set_callback, &the_config_set);
}