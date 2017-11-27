void module_register(void) {
  plugin_register_config("hddtemp", hddtemp_config, config_keys,
                         config_keys_num);
  plugin_register_read("hddtemp", hddtemp_read);
}