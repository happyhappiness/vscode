void module_register(void) {
  plugin_register_config("ntpd", ntpd_config, config_keys, config_keys_num);
  plugin_register_read("ntpd", ntpd_read);
}