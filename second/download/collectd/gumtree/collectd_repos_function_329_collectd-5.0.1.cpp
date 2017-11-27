void module_register (void)
{
	plugin_register_config ("apcups", apcups_config, config_keys,
			config_keys_num);
	plugin_register_read ("apcups", apcups_read);
	plugin_register_shutdown ("apcups", apcups_shutdown);
}