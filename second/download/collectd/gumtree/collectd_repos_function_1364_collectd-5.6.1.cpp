void module_register(void) {
  plugin_register_config(
    "fhcount", fhcount_config, config_keys, config_keys_num);
  plugin_register_read("fhcount", fhcount_read);
}