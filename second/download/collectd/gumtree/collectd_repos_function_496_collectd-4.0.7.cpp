void module_register (void)
{
#if MYSQL_HAVE_READ
	plugin_register_config ("mysql", config, config_keys, config_keys_num);
	plugin_register_read ("mysql", mysql_read);
#endif /* MYSQL_HAVE_READ */
}