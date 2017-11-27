void module_register(void) {
  plugin_register_config("smart", smart_config, config_keys, config_keys_num);
  plugin_register_init("smart", smart_init);
  plugin_register_read("smart", smart_read);
}