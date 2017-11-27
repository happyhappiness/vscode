void module_register(void) {
  plugin_register_init("mic", mic_init);
  plugin_register_shutdown("mic", mic_shutdown);
  plugin_register_read("mic", mic_read);
  plugin_register_config("mic", mic_config, config_keys, config_keys_num);
}