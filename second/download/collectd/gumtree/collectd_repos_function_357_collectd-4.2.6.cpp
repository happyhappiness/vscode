void module_register (void)
{
	plugin_register_config ("tcpconns", conn_config,
			config_keys, config_keys_num);
#if KERNEL_LINUX
	plugin_register_init ("tcpconns", conn_init);
#endif
	plugin_register_read ("tcpconns", conn_read);
}