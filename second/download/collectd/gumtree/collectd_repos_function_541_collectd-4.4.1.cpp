void module_register (void)
{
	plugin_register_config ("dns", dns_config, config_keys, config_keys_num);
	plugin_register_init ("dns", dns_init);
	plugin_register_read ("dns", dns_read);
}