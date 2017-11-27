void module_register(void) {
  plugin_register_config("lpar", lpar_config, config_keys, config_keys_num);
  plugin_register_init("lpar", lpar_init);
  plugin_register_read("lpar", lpar_read);
}