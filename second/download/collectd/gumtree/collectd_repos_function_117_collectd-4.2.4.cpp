void module_register (void)
{
	plugin_register_config ("apache", config,
			config_keys, config_keys_num);
	plugin_register_init ("apache", init);
	plugin_register_read ("apache", apache_read);
}