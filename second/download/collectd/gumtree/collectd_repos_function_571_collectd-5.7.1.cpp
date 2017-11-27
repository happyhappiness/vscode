void module_register(void) {
  plugin_register_config("ascent", ascent_config, config_keys, config_keys_num);
  plugin_register_init("ascent", ascent_init);
  plugin_register_read("ascent", ascent_read);
}