void module_register (void)
{
#if PROCESSES_HAVE_READ
#if HAVE_THREAD_INFO | KERNEL_LINUX
	plugin_register_config ("processes", ps_config,
			config_keys, config_keys_num);
#endif
	plugin_register_init ("processes", ps_init);
	plugin_register_read ("processes", ps_read);
#endif /* PROCESSES_HAVE_READ */
}