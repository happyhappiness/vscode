void module_register(void) {
  plugin_register_config("nut", nut_config, config_keys, config_keys_num);
  plugin_register_init("nut", nut_init);
  plugin_register_shutdown("nut", nut_shutdown);
}