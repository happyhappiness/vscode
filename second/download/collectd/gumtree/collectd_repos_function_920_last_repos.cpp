void module_register(void) {
  plugin_register_init(PLUGIN_NAME, turbostat_init);
  plugin_register_config(PLUGIN_NAME, turbostat_config, config_keys,
                         config_keys_num);
}