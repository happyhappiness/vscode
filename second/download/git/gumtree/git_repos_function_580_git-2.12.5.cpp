void git_config(config_fn_t fn, void *data)
{
	git_config_check_init();
	configset_iter(&the_config_set, fn, data);
}