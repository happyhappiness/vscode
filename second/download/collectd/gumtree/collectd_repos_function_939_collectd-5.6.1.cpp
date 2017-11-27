void module_register (void)
{
	plugin_register_config ("tcpconns", conn_config,
			config_keys, config_keys_num);
#if KERNEL_LINUX
	plugin_register_init ("tcpconns", conn_init);
#elif HAVE_SYSCTLBYNAME
	/* no initialization */
#elif HAVE_LIBKVM_NLIST
	plugin_register_init ("tcpconns", conn_init);
#elif KERNEL_AIX
	/* no initialization */
#endif
	plugin_register_read ("tcpconns", conn_read);
}