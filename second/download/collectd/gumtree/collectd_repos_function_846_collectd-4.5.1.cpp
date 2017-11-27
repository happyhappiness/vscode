void module_register (void)
{
	plugin_register_config ("network", network_config,
			config_keys, config_keys_num);
	plugin_register_init   ("network", network_init);
	plugin_register_flush   ("network", network_flush);
}