void module_register(void) {
  plugin_register_config("madwifi", madwifi_config, config_keys,
                         config_keys_num);

  plugin_register_read("madwifi", madwifi_read);
}