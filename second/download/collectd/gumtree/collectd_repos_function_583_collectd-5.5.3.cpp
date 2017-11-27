void module_register (void)
{
	plugin_register_config ("load", load_config, config_keys, config_keys_num);
	plugin_register_read ("load", load_read);
}