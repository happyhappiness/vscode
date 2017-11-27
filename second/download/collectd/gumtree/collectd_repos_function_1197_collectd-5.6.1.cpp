void module_register(void)
{
	/*
	 * Mandatory module_register function
	 */
	plugin_register_config ("teamspeak2", tss2_config,
			config_keys, config_keys_num);
	plugin_register_read ("teamspeak2", tss2_read);
	plugin_register_shutdown ("teamspeak2", tss2_shutdown);
}