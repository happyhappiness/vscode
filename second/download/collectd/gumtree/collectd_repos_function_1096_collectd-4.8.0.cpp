void module_register (void)
{
	plugin_register_config ("csv", csv_config,
			config_keys, config_keys_num);
	plugin_register_write ("csv", csv_write, /* user_data = */ NULL);
}