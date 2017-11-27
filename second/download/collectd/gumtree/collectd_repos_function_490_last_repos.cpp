void module_register(void) {
  plugin_register_config("nfs", nfs_config, config_keys, config_keys_num);
  plugin_register_init("nfs", nfs_init);
  plugin_register_read("nfs", nfs_read);
}