void module_register (void)
{
#if MBMON_HAVE_READ
	plugin_register_config ("mbmon", mbmon_config, config_keys, config_keys_num);
	plugin_register_read ("mbmon", mbmon_read);
#endif /* MBMON_HAVE_READ */
}