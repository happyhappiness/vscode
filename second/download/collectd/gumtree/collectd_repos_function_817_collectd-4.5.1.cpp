void module_register (void)
{
	plugin_register_config ("mysql", config, config_keys, config_keys_num);
	plugin_register_read ("mysql", mysql_read);
}