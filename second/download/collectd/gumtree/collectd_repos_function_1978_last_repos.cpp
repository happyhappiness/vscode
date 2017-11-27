void module_register(void) {
  plugin_register_complex_config("memory", memory_config);
  plugin_register_init("memory", memory_init);
  plugin_register_read("memory", memory_read);
}