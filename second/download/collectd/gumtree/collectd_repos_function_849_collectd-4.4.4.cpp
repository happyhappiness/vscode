void module_register (void)
{
	plugin_register_config ("uuid", uuid_config,
                            config_keys, NR_CONFIG_KEYS);
	plugin_register_init ("uuid", uuid_init);
}