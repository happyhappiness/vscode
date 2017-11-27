void module_register (void)
{
	plugin_register_config ("logfile", logfile_config,
			config_keys, config_keys_num);
	plugin_register_log ("logfile", logfile_log);
	plugin_register_notification ("logfile", logfile_notification);
}