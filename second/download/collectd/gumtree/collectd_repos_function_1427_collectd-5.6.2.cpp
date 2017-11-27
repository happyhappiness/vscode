void module_register(void) {
  plugin_register_config("ipmi", c_ipmi_config, config_keys, config_keys_num);
  plugin_register_init("ipmi", c_ipmi_init);
  plugin_register_read("ipmi", c_ipmi_read);
  plugin_register_shutdown("ipmi", c_ipmi_shutdown);
}