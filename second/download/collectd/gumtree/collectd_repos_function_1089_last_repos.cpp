void module_register(void) {
  plugin_register_config("mbmon", mbmon_config, config_keys, config_keys_num);
  plugin_register_read("mbmon", mbmon_read);
}