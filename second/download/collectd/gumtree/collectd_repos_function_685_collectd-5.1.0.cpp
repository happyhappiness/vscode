void module_register (void)
{
	openlog ("collectd", LOG_CONS | LOG_PID, LOG_DAEMON);

	plugin_register_config ("syslog", sl_config, config_keys, config_keys_num);
	plugin_register_log ("syslog", sl_log, /* user_data = */ NULL);
	plugin_register_notification ("syslog", sl_notification, NULL);
	plugin_register_shutdown ("syslog", sl_shutdown);
}