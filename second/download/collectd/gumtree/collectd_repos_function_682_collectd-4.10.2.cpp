void module_register (void) /* {{{ */
{
	plugin_register_config ("memcached", memcached_config, config_keys, config_keys_num);
	plugin_register_read ("memcached", memcached_read);
}