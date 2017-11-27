void module_register(void) {
  plugin_register_config("protocols", protocols_config, config_keys,
                         config_keys_num);
  plugin_register_read("protocols", protocols_read);
}