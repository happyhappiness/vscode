void module_register (void)
{
	plugin_register_config ("interface", interface_config,
			config_keys, config_keys_num);
#if HAVE_LIBKSTAT
	plugin_register_init ("interface", interface_init);
#endif
#if INTERFACE_HAVE_READ
	plugin_register_read ("interface", interface_read);
#endif
}