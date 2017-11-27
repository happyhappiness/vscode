void module_register (void)
{
	plugin_register_config ("processes", ps_config,
			config_keys, config_keys_num);
	plugin_register_init ("processes", ps_init);
	plugin_register_read ("processes", ps_read);
}