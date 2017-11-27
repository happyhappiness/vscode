void module_register(void) {
  plugin_register_config("openvpn", openvpn_config, config_keys,
                         config_keys_num);
  plugin_register_init("openvpn", openvpn_init);
}