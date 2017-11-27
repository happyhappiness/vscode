void module_register(void) {
  plugin_register_config("df", df_config, config_keys, config_keys_num);
  plugin_register_init("df", df_init);
  plugin_register_read("df", df_read);
}