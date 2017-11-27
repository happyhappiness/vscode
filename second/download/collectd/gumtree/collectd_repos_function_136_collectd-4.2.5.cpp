void module_register (void)
{
	plugin_register_config ("ping", ping_config,
			config_keys, config_keys_num);
	plugin_register_init ("ping", ping_init);
	plugin_register_read ("ping", ping_read);
}