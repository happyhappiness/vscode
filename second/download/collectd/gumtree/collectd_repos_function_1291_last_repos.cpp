void module_register(void) {
  plugin_register_config(PLUGIN_NAME_SHORT, chrony_config, g_config_keys,
                         g_config_keys_num);
  plugin_register_read(PLUGIN_NAME_SHORT, chrony_read);
  plugin_register_shutdown(PLUGIN_NAME_SHORT, chrony_shutdown);
}