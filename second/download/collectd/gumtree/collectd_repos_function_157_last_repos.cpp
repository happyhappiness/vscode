void module_register(void) {
  plugin_register_config("irq", irq_config, config_keys, config_keys_num);
  plugin_register_read("irq", irq_read);
}