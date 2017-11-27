void module_register(void) {
  plugin_register_config("md", md_config, config_keys, config_keys_num);
  plugin_register_read("md", md_read);
}