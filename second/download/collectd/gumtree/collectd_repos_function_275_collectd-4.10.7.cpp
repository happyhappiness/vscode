void module_register (void)
{
	plugin_register_config ("thermal", thermal_config,
			config_keys, STATIC_ARRAY_SIZE(config_keys));
	plugin_register_init ("thermal", thermal_init);
	plugin_register_shutdown ("thermal", thermal_shutdown);
}