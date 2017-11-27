void module_register (void)
{
#if HAVE_SWAPCTL && HAVE_SWAPCTL_TWO_ARGS
	plugin_register_config ("swap", swap_config, config_keys, config_keys_num);
#endif
	plugin_register_init ("swap", swap_init);
	plugin_register_read ("swap", swap_read);
}