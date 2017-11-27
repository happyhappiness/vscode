void module_register(void) {
  plugin_register_init("notify_email", notify_email_init);
  plugin_register_shutdown("notify_email", notify_email_shutdown);
  plugin_register_config("notify_email", notify_email_config, config_keys,
                         config_keys_num);
  plugin_register_notification("notify_email", notify_email_notification,
                               /* user_data = */ NULL);
}