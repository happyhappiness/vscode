void module_register (void)
{
#if NTPD_HAVE_READ
	plugin_register_config ("ntpd", ntpd_config,
			config_keys, config_keys_num);
	plugin_register_read ("ntpd", ntpd_read);
#endif /* NTPD_HAVE_READ */
}