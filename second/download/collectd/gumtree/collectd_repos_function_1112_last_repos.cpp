void module_register(void) {
  plugin_register_complex_config("notify_nagios", nagios_config);
  plugin_register_notification("notify_nagios", nagios_notify, NULL);
}