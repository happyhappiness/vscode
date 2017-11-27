void module_register(void) {
  plugin_register_config("zookeeper", zookeeper_config, config_keys,
                         config_keys_num);
  plugin_register_read("zookeeper", zookeeper_read);
}