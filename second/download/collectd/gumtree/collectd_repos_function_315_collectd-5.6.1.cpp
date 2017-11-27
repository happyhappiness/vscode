void module_register (void)
{
	plugin_register_init ("cpu", init);
	plugin_register_config ("cpu", cpu_config, config_keys, config_keys_num);
	plugin_register_read ("cpu", cpu_read);
}