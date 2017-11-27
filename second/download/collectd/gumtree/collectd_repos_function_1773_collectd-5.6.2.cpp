void module_register(void) {
  plugin_register_config("olsrd", olsrd_config, config_keys, config_keys_num);
  plugin_register_read("olsrd", olsrd_read);
  plugin_register_shutdown("olsrd", olsrd_shutdown);
}