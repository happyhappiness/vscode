void module_register (void)
{
#if HDDTEMP_HAVE_READ
	plugin_register_config ("hddtemp", hddtemp_config,
			config_keys, config_keys_num);
	plugin_register_init ("hddtemp", hddtemp_init);
	plugin_register_read ("hddtemp", hddtemp_read);
#endif /* HDDTEMP_HAVE_READ */
}