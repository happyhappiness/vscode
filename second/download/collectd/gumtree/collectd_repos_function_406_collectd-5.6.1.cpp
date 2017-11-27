void module_register (void)
{
	plugin_register_config ("unixsock", us_config,
			config_keys, config_keys_num);
	plugin_register_init ("unixsock", us_init);
	plugin_register_shutdown ("unixsock", us_shutdown);
}