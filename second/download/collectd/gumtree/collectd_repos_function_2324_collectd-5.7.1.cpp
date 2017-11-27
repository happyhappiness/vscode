void module_register(void) {
  plugin_register_config("conntrack", conntrack_config, config_keys,
                         config_keys_num);
  plugin_register_read("conntrack", conntrack_read);
}