void module_register(void) {
  plugin_register_config("email", email_config, config_keys, config_keys_num);
  plugin_register_init("email", email_init);
  plugin_register_read("email", email_read);
  plugin_register_shutdown("email", email_shutdown);
}