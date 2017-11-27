void module_register (void)
{
#if SWAP_HAVE_CONFIG
	plugin_register_config ("swap", swap_config, config_keys, config_keys_num);
#endif
	plugin_register_init ("swap", swap_init);
	plugin_register_read ("swap", swap_read);
}