void module_register(void) {
  plugin_register_config("cgroups", cgroups_config, config_keys,
                         config_keys_num);
  plugin_register_init("cgroups", cgroups_init);
  plugin_register_read("cgroups", cgroups_read);
}