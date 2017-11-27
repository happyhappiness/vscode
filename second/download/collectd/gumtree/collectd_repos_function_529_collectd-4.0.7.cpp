void module_register (void)
{
#if SENSORS_HAVE_READ
	plugin_register_config ("sensors", sensors_config,
			config_keys, config_keys_num);
	plugin_register_read ("sensors", sensors_read);
	plugin_register_shutdown ("sensors", sensors_shutdown);
#endif
}